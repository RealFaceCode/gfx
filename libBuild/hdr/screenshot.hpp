#pragma once 

#include "defines.hpp"
#include <string>

namespace gfx
{
    enum class ScreenshotFormat
    {
        PNG,
        JPG,
        BMP,
        TGA,
        RAW
    };

    struct GFX_API Screenshot
    {
    public:
        Screenshot();
        Screenshot(unsigned char* data, int width, int height, int channels, ScreenshotFormat format);
        Screenshot(unsigned char* data, int width, int height, int channels, int quality, ScreenshotFormat format);
        ~Screenshot();

        uint8_t* data;
        int width;
        int height;
        int channels;
        int quality;
        ScreenshotFormat format;
    };

    GFX_API Screenshot MakeScreenshot(int x, int y, int width, int height, ScreenshotFormat format = ScreenshotFormat::PNG, int quality = 100);
    GFX_API bool WriteScreenshot(const std::string& path, const Screenshot& screenshot);
}