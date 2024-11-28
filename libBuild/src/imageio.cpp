#include "imageio.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <lc.hpp>
#include "fios.hpp"
#include "fioc.hpp"

namespace gfx
{
    unsigned char* LoadImageFromFile(const std::string& path, int& width, int& height, int& channels, bool flip)
    {
        stbi_set_flip_vertically_on_load(flip);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            lc::Log<gfx::GFX>("ERROR", "Failed to load image: {}", path);
        }
        
        return data;
    }

    Image LoadAsImage(const std::string& path, bool flip)
    {
        Image image;
        image.data = LoadImageFromFile(path, image.width, image.height, image.channels, flip);
        return image;
    }

    bool WriteImagePNG(const std::string& path, unsigned char* data, int width, int height, int channels)
    {
        std::string fullPath = path + ".png";
        eutil::fioc::CreateDirectoryRecursive(fullPath.c_str());
        stbi_flip_vertically_on_write(true);
        bool result = stbi_write_png(fullPath.c_str(), width, height, channels, data, width * channels);
        if (!result)
            lc::Log<gfx::GFX>("ERROR", "Failed to write image: {}", path);

        return result;
    }

    bool WriteImagePNG(const std::string& path, const Image& image)
    {
        return WriteImagePNG(path, image.data, image.width, image.height, image.channels);
    }

    bool WriteImageJPG(const std::string& path, unsigned char* data, int width, int height, int channels, int quality)
    {
        std::string fullPath = path + ".jpg";
        stbi_flip_vertically_on_write(true);
        int result = stbi_write_jpg(fullPath.c_str(), width, height, channels, data, quality);
        if (!result)
            lc::Log<gfx::GFX>("ERROR", "Failed to write image: {}", path);

        return result;
    }

    bool WriteImageJPG(const std::string& path, const Image& image, int quality)
    {
        return WriteImageJPG(path, image.data, image.width, image.height, image.channels, quality);
    }

    bool WriteImageBMP(const std::string& path, unsigned char* data, int width, int height, int channels)
    {
        std::string fullPath = path + ".bmp";
        stbi_flip_vertically_on_write(true);
        bool result = stbi_write_bmp(fullPath.c_str(), width, height, channels, data);
        if (!result)
            lc::Log<gfx::GFX>("ERROR", "Failed to write image: {}", path);

        return result;
    }

    bool WriteImageBMP(const std::string& path, const Image& image)
    {
        return WriteImageBMP(path, image.data, image.width, image.height, image.channels);
    }

    bool WriteImageTGA(const std::string& path, unsigned char* data, int width, int height, int channels)
    {
        std::string fullPath = path + ".tga";
        stbi_flip_vertically_on_write(true);
        bool result = stbi_write_tga(fullPath.c_str(), width, height, channels, data);
        if (!result)
            lc::Log<gfx::GFX>("ERROR", "Failed to write image: {}", path);

        return result;
    }

    bool WriteImageTGA(const std::string& path, const Image& image)
    {
        return WriteImageTGA(path, image.data, image.width, image.height, image.channels);
    }

    bool WriteImageRAW(const std::string& path, unsigned char* data, int width, int height, int channels)
    {
        std::string fullPath = path + ".raw";

        //flip vertically
        unsigned char* flippedData = new unsigned char[width * height * channels];

        for (int y = 0; y < height; y++)
        {
            int flippedY = height - 1 - y;
            for (int x = 0; x < width; x++)
            {
                for (int c = 0; c < channels; c++)
                {
                    flippedData[(y * width + x) * channels + c] = data[(flippedY * width + x) * channels + c];
                }
            }
        }

        bool result = eutil::fios::WriteDataToFile(fullPath.c_str(), flippedData, width * height * channels);

        if (!result)
            lc::Log<gfx::GFX>("ERROR", "Failed to write image: {}", path);

        return result;
    }

    bool WriteImageRAW(const std::string& path, const Image& image)
    {
        return WriteImageRAW(path, image.data, image.width, image.height, image.channels);
    }
}