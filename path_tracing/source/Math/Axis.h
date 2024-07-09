#pragma once

#include "Vector.h"

namespace Math
{

enum CoordAxis : uint8_t
{
    CoordAxis_X,
    CoordAxis_Y,
    CoordAxis_Z,
    CoordAxis_Count
};

// NOTE: this isn't the same as longestAxis
CoordAxis maxAxis(float3 v);

} // namespace Math


inline Math::CoordAxis Math::maxAxis(float3 v)
{
    if (v.x > v.y)
    {
        if (v.x > v.z)
        {
            return CoordAxis_X;
        }
        else
        {
            return CoordAxis_Z;
        }
    }
    else
    {
        if (v.y > v.z)
        {
            return CoordAxis_Y;
        }
        else
        {
            return CoordAxis_Z;
        }
    }
}
