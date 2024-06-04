// https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/

// Note that BVH isn't space partition.

#pragma once

#include "Math/Vector.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Item
///////////////////////////////////////////////////////////////////////////////

struct Tri
{
    Math::float3 vertex0;
    Math::float3 vertex1;
    Math::float3 vertex2;
    Math::float3 centroid;
};


///////////////////////////////////////////////////////////////////////////////
// Item
///////////////////////////////////////////////////////////////////////////////

struct BVHNode
{
    static constexpr uint32_t kChildCount = 2;

    Math::float3 aabbMin;       // 12 bytes
    Math::float3 aabbMax;       // 12 bytes
    uint32_t firstChild;        // 4 bytes
    uint32_t firstItemRef;      // 4 bytes
    uint32_t itemCount;         // 4 bytes
};

class BVH
{
public:
    using Item = Tri;

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
    uint32_t nodeCount;

    uint32_t allocNode() { uint32_t nodeIndex = uint32_t(nodePool.size()); nodePool.emplace_back(); return nodeIndex; }
    void updateNodeBounds(BVHNode& node);    
    void subdivideNode(BVHNode& node);

public:
    BVH(const Item* items, uint32_t itemCount);
};