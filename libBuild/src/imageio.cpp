#include "imageio.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <lc.hpp>

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
}