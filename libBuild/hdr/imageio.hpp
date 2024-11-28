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

    GFX_API bool WriteImagePNG(const std::string& path, unsigned char* data, int width, int height, int channels);
    GFX_API bool WriteImagePNG(const std::string& path, const Image& image);
    GFX_API bool WriteImageJPG(const std::string& path, unsigned char* data, int width, int height, int channels, int quality = 100);
    GFX_API bool WriteImageJPG(const std::string& path, const Image& image, int quality = 100);
    GFX_API bool WriteImageBMP(const std::string& path, unsigned char* data, int width, int height, int channels);
    GFX_API bool WriteImageBMP(const std::string& path, const Image& image);
    GFX_API bool WriteImageTGA(const std::string& path, unsigned char* data, int width, int height, int channels);
    GFX_API bool WriteImageTGA(const std::string& path, const Image& image);
    GFX_API bool WriteImageRAW(const std::string& path, unsigned char* data, int width, int height, int channels);
    GFX_API bool WriteImageRAW(const std::string& path, const Image& image);
}