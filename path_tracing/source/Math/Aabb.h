#pragma once

#include "Vector.h"
#include <limits>

namespace Math
{

struct Aabb
{
    float3 min;
    float3 max;

    Aabb();
    Aabb(const float3& min, const float3& max);

    Aabb& expand(const float3& p);

    float3 extent() const;
    float area() const;
};

Aabb::Aabb()
    : min( std::numeric_limits<float>::max())
    , max(-std::numeric_limits<float>::max())
{
}

Aabb::Aabb(const float3& min, const float3& max)
    : min(min)
    , max(max)
{    
}

inline Aabb& Aabb::expand(const float3& p)
{
    min = Math::min(min, p);
    max = Math::max(max, p);
    return *this;
}

inline float3 Aabb::extent() const
{
    return max - min;
}

inline float Aabb::area() const
{
    float3 e = extent();
    return (e.x * e.y + e.x * e.z + e.y * e.z) * 2.f;
}

} // namespace Math