#pragma once

#include "../Math/Color.h"
#include <cstdint>

struct Image
{
    uint32_t width;
    uint32_t height;
    Math::color3b* pixels;

    Image(uint32_t width, uint32_t height);
    ~Image();

    Math::color3b& operator()(uint32_t x, uint32_t y) { return pixels[y*width + x]; }
    const Math::color3b& operator()(uint32_t x, uint32_t y) const { return pixels[y*width + x]; }

    void save(const char* filepath);
};
