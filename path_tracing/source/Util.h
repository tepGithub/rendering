#pragma once

#include <cstdint>

uint32_t RandomUInt();
float RandomFloat();
float Rand( float range );
uint32_t RandomUInt( uint32_t& seed );
float RandomFloat( uint32_t& seed );


////////////////////////////////////////////////////////////////////
// Timer
////////////////////////////////////////////////////////////////////
#include <chrono>

class Timer
{
    using clock = std::chrono::high_resolution_clock;
    using time_point = clock::time_point;

    time_point start;

public:
    Timer()
        : start(clock::now())
    {
    }

    int64_t duration() const
    {
        time_point current = clock::now();

        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - start);
        return duration.count();
    }
};