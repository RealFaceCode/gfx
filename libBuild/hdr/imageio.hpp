#pragma once

#include "defines.hpp"
#include <string>

namespace gfx
{
    struct Image
    {
        unsigned char* data;
        int width;
        int height;
        int channels;
    };

    GFX_API unsigned char* LoadImageFromFile(const std::string& path, int& width, int& height, int& channels, bool flip = true);
    GFX_API Image LoadAsImage(const std::string& path, bool flip = true);
}