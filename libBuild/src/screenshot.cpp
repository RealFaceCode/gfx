#include "screenshot.hpp"
#include <lc.hpp>
#include "imageio.hpp"
#include <glad/glad.h>
#include <util.hpp>
#include <format>

namespace gfx
{
    Screenshot::Screenshot()
        : data(nullptr), width(0), height(0), channels(0), quality(100), format(ScreenshotFormat::PNG)
    {}

    Screenshot::Screenshot(unsigned char* data, int width, int height, int channels, ScreenshotFormat format)
        : data(data), width(width), height(height), channels(channels), quality(100), format(format)
    {}

    Screenshot::Screenshot(unsigned char* data, int width, int height, int channels, int quality, ScreenshotFormat format)
        : data(data), width(width), height(height), channels(channels), quality(quality), format(format)
    {}

    Screenshot::~Screenshot()
    {
        if (data)
            delete[] data;
        data = nullptr;
    }

    Screenshot MakeScreenshot(int x, int y, int width, int height, ScreenshotFormat format, int quality)
    {
        Screenshot screenshot;
        screenshot.format = format;
        screenshot.quality = quality;
        screenshot.width = width;
        screenshot.height = height;

        screenshot.data = new uint8_t[width * height * 3];
        glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, screenshot.data);
        return screenshot;
    }

    bool WriteScreenshot(const std::string& path, const Screenshot& screenshot)
    {
        std::string time = eutil::getCurrentTime("%Y%m%d_%H%M%S");
        std::string name = "screenshot";
        auto fullPath = std::format("{}/{}{}", path, name, time);

        switch (screenshot.format)
        {
        case ScreenshotFormat::PNG:
            return WriteImagePNG(fullPath, screenshot.data, screenshot.width, screenshot.height, 3);
        case ScreenshotFormat::JPG:
            return WriteImageJPG(fullPath, screenshot.data, screenshot.width, screenshot.height, 3, screenshot.quality);
        case ScreenshotFormat::BMP:
            return WriteImageBMP(fullPath, screenshot.data, screenshot.width, screenshot.height, 3);
        case ScreenshotFormat::TGA:
            return WriteImageTGA(fullPath, screenshot.data, screenshot.width, screenshot.height, 3);
        case ScreenshotFormat::RAW:
            return WriteImageRAW(fullPath, screenshot.data, screenshot.width, screenshot.height, 3);
        default:
        lc::Log<gfx::GFX>("ERROR", "Invalid screenshot format");
            return false;
        }
    }
}