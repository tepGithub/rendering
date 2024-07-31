#include "BVH.h"
#include "Math/Aabb.h"
#include "Math/Intersect.h"
#include <cassert>
using namespace Math;

static constexpr float kLargeNumber = 1e30f;

///////////////////////////////////////////////////////////////////////////////
// Item
///////////////////////////////////////////////////////////////////////////////
static float3 getAabbMin(const BVH::Item& item)
{
    return min3(item.vertex0, item.vertex1, item.vertex2);
}
static float3 getAabbMax(const BVH::Item& item)
{
    return max3(item.vertex0, item.vertex1, item.vertex2);
}

///////////////////////////////////////////////////////////////////////////////
// Nodes
///////////////////////////////////////////////////////////////////////////////

float BVH::evaluateSAH(const BVHNode& node, Math::CoordAxis axis, float splitPos)
{
    Aabb leftBox(float3(kLargeNumber), float3(-kLargeNumber));
    Aabb rightBox(float3(kLargeNumber), float3(-kLargeNumber));
    int leftCount = 0;
    int rightCount = 0;

    for (uint32_t i=0; i<node.itemCount; i++)
    {
        const Item& item = getItem(node.firstItemRef() + i);
        if (item.centroid[axis] < splitPos)
        {
            leftCount++;
            leftBox.expand(item.vertex0);
            leftBox.expand(item.vertex1);
            leftBox.expand(item.vertex2);
        }
        else
        {
            rightCount++;
            rightBox.expand(item.vertex0);
            rightBox.expand(item.vertex1);
            rightBox.expand(item.vertex2);
        }
    }

    // Cost of making a partition:
    //   C = C_trav + p_a * C_a + p_b * C_b
    //
    // C_trav is the cost of traversing an interior node (e.g. bounding box test)
    // C_a and C_b are the costs of intersection with the resultant child subtrees
    // p_a and p_b are the probability a ray intersects the bbox of the child nodes A and B

    // Let's just simplify for now
    float cost = leftCount * leftBox.area() + rightCount * rightBox.area();
    assert(cost > 0.0f);
    return cost;    
}

// axis=0 means split plane: x=value
float BVH::computeSplitPlane(const BVHNode& node, CoordAxis* outAxis, float* outSplitPos)
{
#if 1
    CoordAxis bestAxis = CoordAxis_Count;
    float bestPos = 0.0f;
    float bestCost = 1e30f;

    for (uint8_t axisIndex = 0; axisIndex < CoordAxis_Count; axisIndex++)
    {
        CoordAxis axis = CoordAxis(axisIndex);
        for (uint32_t i=0; i<node.itemCount; i++)
        {
            const Item& item = getItem(node.firstItemRef() + i);
            float candidatePos = item.centroid[axis];
            float cost = evaluateSAH(node, axis, candidatePos);
            if (cost < bestCost)
            {
                bestPos = candidatePos;
                bestAxis = axis;
                bestCost = cost;
            }
        }
    }

    *outAxis = bestAxis;
    *outSplitPos = bestPos;
    return bestCost;
#else
    float3 extent = node.aabbMax - node.aabbMin;
    CoordAxis axis = maxAxis(extent);

    *outAxis = axis;
    *outSplitPos = node.aabbMin[axis] + extent[axis] * 0.5f;
    return 0.0f;
#endif
}

// Worst case number of BVHNode for N items are simply: 2N - 1 (sum the nodes of full binary tree)
// Use geometric series to compute worst case node count (a = 1, r = 2, n = log2(N) + 1)
// = a * (1 - r^n) / (1 - r)
// = 1 * (1 - 2^(log2(N) + 1)) / (1 - 2)
// = (1 - 2^log2(N) * 2) / (-1)
// = (1 - N * 2) / (-1)
// = 2*N - 1
static uint32_t computeMaxNodeCount(uint32_t N)
{
    return 2 * N - 1;
}


///////////////////////////////////////////////////////////////////////////////
// BVH
///////////////////////////////////////////////////////////////////////////////

BVH::BVH(const Item* items, uint32_t _itemCount)
    : items(items)
    , itemCount(_itemCount)
{
    // items
    itemRefs.resize(itemCount);
    for (uint32_t i=0; i<itemCount; i++)
        itemRefs[i] = i;

    // nodes
    uint32_t maxNodeCount = computeMaxNodeCount(itemCount);

    // reserve worst case for now
    nodePool.reserve(maxNodeCount);

    // allocate root node and assign all items to the root
    rootNodeIndex = allocNode();

    BVHNode& root = nodePool[rootNodeIndex];
    root.initLeafNode(0, itemCount);

    updateNodeBounds(root);

    subdivideNode(root);
}

// partition items in node into two partition: partition0 and partition1.
// returns number of item in partition0
uint32_t BVH::partitionItems(BVHNode& node, Math::CoordAxis axis, float splitPos)
{
    int i = node.firstItemRef();
    int j = node.firstItemRef() + node.itemCount - 1;
    while (i <= j)
    {
        if (getItem(i).centroid[axis] < splitPos)
        {
            i++;
        }
        else
        {
            std::swap(itemRefs[i], itemRefs[j]);
            j--;
        }
    }
    return (i - node.firstItemRef());
}


void BVH::updateNodeBounds(BVHNode& node)
{
    assert(node.itemCount > 0);
    {
        const Item& item = getItem(node.firstItemRef());
        node.aabbMin = getAabbMin(item);
        node.aabbMax = getAabbMax(item);
    }
    for (uint32_t i=1; i<node.itemCount; i++)
    {
        const Item& item = getItem(node.firstItemRef() + i);
        node.aabbMin = min(node.aabbMin, getAabbMin(item));
        node.aabbMax = max(node.aabbMax, getAabbMax(item));
    }
}

// subdivide
void BVH::subdivideNode(BVHNode& node)
{
    //if (node.itemCount <= 2)
    //    return;

    CoordAxis splitAxis;
    float splitPos;
    float splitCost = computeSplitPlane(node, &splitAxis, &splitPos);

    // if splitting doesn't improve, no need to subdivide
    Aabb nodeAabb(node.aabbMin, node.aabbMax);
    float nodeCost = node.itemCount * nodeAabb.area();    
    if (splitCost >= nodeCost)
        return;

    uint32_t childItemCount0 = partitionItems(node, splitAxis, splitPos);
    
    // we don't need to subdivide if any of the partitions is empty
    if (childItemCount0 == 0 || childItemCount0 == node.itemCount)
        return;

    assert(node.isLeaf());

    // create child nodes
    uint32_t childIndex0 = allocNode();
    BVHNode& child0 = nodePool[childIndex0];
    child0.initLeafNode(node.firstItemRef(), childItemCount0);
    updateNodeBounds(child0);

    uint32_t childIndex1 = allocNode();
    BVHNode& child1 = nodePool[childIndex1];
    child1.initLeafNode(node.firstItemRef() + childItemCount0, node.itemCount - childItemCount0);
    updateNodeBounds(child1);

    // update current node
    assert(childIndex1 == childIndex0 + 1);
    node.initInternalNode(childIndex0);

    subdivideNode(child0);
    subdivideNode(child1);
}

void BVH::intersect(Math::Ray& ray, BVHNode& node)
{
    if (intersectRayAabb(ray, node.aabbMin, node.aabbMax) == Ray::kInf)
        return;

    if (node.isLeaf())
    {
        for (uint32_t i=0; i<node.itemCount; i++)
        {
            const Item& item = getItem(node.firstItemRef() + i);
            intersectRayTri(ray, item);
        }
    }
    else
    {
        static_assert(BVHNode::kChildCount == 2);
        intersect(ray, nodePool[node.firstChild()]);
        intersect(ray, nodePool[node.firstChild() + 1]);
    } 
}

void BVH::intersect(Math::Ray& ray)
{
#if 1
    intersect(ray, nodePool[rootNodeIndex]);
#else
    BVHNode* node = &nodePool[rootNodeIndex];

    // check if we hit root node aabb at all
    if (intersectRayAabb(ray, node->aabbMin, node->aabbMax) == Ray::kInf)
        return;

    BVHNode* stack[64];
    uint32_t stackPtr = 0;

    while (1)
    {
        if (node->isLeaf())
        {
            for (uint32_t i=0; i<node->itemCount; i++)
            {
                const Item& item = getItem(node->firstItemRef() + i);
                intersectRayTri(ray, item);
            }
            
            if (stackPtr == 0)
                break;

            node = stack[--stackPtr];
        }
        else
        {
            // we want to traverse front front-to-back
            static_assert(BVHNode::kChildCount == 2);
            BVHNode* child0 = &nodePool[node->firstChild()];
            BVHNode* child1 = &nodePool[node->firstChild() + 1];
            float dist0 = intersectRayAabb(ray, child0->aabbMin, child0->aabbMax);
            float dist1 = intersectRayAabb(ray, child1->aabbMin, child1->aabbMax);

            if (dist0 > dist1)
            {
                std::swap(dist0, dist1);
                std::swap(child0, child1);
            }

            // at this point child0 is the front, child1 is the back
            if (dist0 == Ray::kInf)
            {
                if (stackPtr == 0)
                    break;
                node = stack[--stackPtr];
            }
            else
            {
                node = child0;
                if (dist1 != Ray::kInf) stack[stackPtr++] = child1;
            }
        }
    }
#endif
}
