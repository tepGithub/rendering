#pragma once

#include "Vector.h"

namespace Math
{

struct Tri
{
    Math::float3 vertex0;
    Math::float3 vertex1;
    Math::float3 vertex2;
    Math::float3 centroid;
};

} // namespace Math