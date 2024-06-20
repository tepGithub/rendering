#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
    , pixels(new Pixel[width * height])
{    
}

Image::~Image()
{
    delete [] pixels;    
}

void Image::clear(const Pixel& clearValue)
{
    uint32_t pixelCount = width * height;
    for (uint32_t i=0; i<pixelCount; i++)
        pixels[i] = clearValue;
}

void Image::save(const char* filepath)
{
    stbi_write_png(filepath, width, height, 3, pixels, width * sizeof(pixels[0]));
}