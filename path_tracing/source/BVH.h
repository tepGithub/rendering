// https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/
// https://jacco.ompf2.com/2022/04/18/how-to-build-a-bvh-part-2-faster-rays/

// Note that BVH isn't space partition.

#pragma once

#include "Math/Ray.h"
#include "Math/Tri.h"
#include <vector>


///////////////////////////////////////////////////////////////////////////////
// Node
///////////////////////////////////////////////////////////////////////////////

struct BVHNode
{
    static constexpr uint32_t kChildCount = 2;

    Math::float3 aabbMin;           // 12 bytes
    Math::float3 aabbMax;           // 12 bytes
private:
    uint32_t firstChildOrItemRef;   // 4 bytes
public:
    uint32_t itemCount;             // 4 bytes

    void initLeafNode(uint32_t firstItemRef, uint32_t count)
    {
        firstChildOrItemRef = firstItemRef;
        itemCount = count;
    }
    void initInternalNode(uint32_t firstChild)
    {
        firstChildOrItemRef = firstChild;
        itemCount = 0;
    }

    bool isLeaf() const { return itemCount > 0; }
    uint32_t firstChild() const { assert(!isLeaf()); return firstChildOrItemRef; }
    uint32_t firstItemRef() const { assert(isLeaf()); return firstChildOrItemRef; }
};
static_assert(sizeof(BVHNode) == 32);

class BVH
{
public:
    using Item = Math::Tri;

private:
    using ItemRefs = std::vector<uint32_t>;
    using NodePool = std::vector<BVHNode>;

    // items
    const Item* items;
    ItemRefs itemRefs;
    uint32_t itemCount;

    const Item& getItem(uint32_t itemRefIndex) { return items[itemRefs[itemRefIndex]]; }
    uint32_t partitionItems(BVHNode& node, int axis, float splitPos);

    // nodes
    NodePool nodePool;
    uint32_t rootNodeIndex;
    //uint32_t nodeCount;

    uint32_t allocNode() { uint32_t nodeIndex = uint32_t(nodePool.size()); nodePool.emplace_back(); return nodeIndex; }
    void updateNodeBounds(BVHNode& node);    
    void subdivideNode(BVHNode& node);

    void intersect(Math::Ray& ray, BVHNode& node);

public:
    BVH(const Item* items, uint32_t itemCount);

    void intersect(Math::Ray& ray) { intersect(ray, nodePool[rootNodeIndex]); }
};