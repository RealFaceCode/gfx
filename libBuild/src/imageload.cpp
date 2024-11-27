#include "imageload.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <lc.hpp>

namespace gfx
{
    Image LoadImageFromFile(const std::string& path, bool flip)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(flip);
        uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            lc::Log<gfx::GL>("ERROR", "Failed to load image: {}", path);
            return Image();
        }

        return Image(data, width, height, channels);
    }
}