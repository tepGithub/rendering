#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
    , pixels(new Math::color3b[width * height])
{    
}

Image::~Image()
{
    delete [] pixels;    
}

void Image::save(const char* filepath)
{
    stbi_write_png(filepath, width, height, 3, pixels, width * sizeof(pixels[0]));
}