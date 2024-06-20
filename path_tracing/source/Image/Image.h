#pragma once

#include "../Math/Color.h"
#include <cstdint>

struct Image
{
    using Pixel = Math::color3b;

    uint32_t width;
    uint32_t height;
    Pixel* pixels;

    Image(uint32_t width, uint32_t height);
    ~Image();

    Pixel& operator()(uint32_t x, uint32_t y) { return pixels[y*width + x]; }
    const Pixel& operator()(uint32_t x, uint32_t y) const { return pixels[y*width + x]; }

    void clear(const Pixel& clearValue);
    void save(const char* filepath);
};
