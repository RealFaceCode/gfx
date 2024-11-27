#pragma once

#include "defines.hpp"
#include <cstdint>
#include <glm/glm.hpp>

namespace gfx
{
    class GFX_API Image
    {
    public:
        Image();
        Image(uint8_t* data, int width, int height, int channels, bool flip = false);
        Image(const Image& other);
        Image(Image&& other);
        Image& operator=(Image&& other);
        ~Image();

        void setData(uint8_t* data, int width, int height, int channels, bool flip = false);

        const uint8_t* getData() const;
        const glm::vec2& getSize() const;
        const int& getChannels() const;

    private:
        uint8_t* data;
        glm::vec2 size;
        int channels;
    };
}