#pragma once

#include "Vector.h"

namespace Math
{
    struct Ray
    {
        static constexpr float kInf = 1e30f;

        Math::float3 O;
        Math::float3 D;
        float t = Ray::kInf;
    };

} // namespace Math