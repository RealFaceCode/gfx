#pragma once

#include "defines.hpp"
#include <string>
#include <glad/glad.h>
#include <memory>

namespace gfx
{
    enum class TextureDataType;
    enum class TextureFormat;
    enum class TextureType;

    class GFX_API Texture
    {
    public:
        Texture();
        Texture(uint32_t texture, TextureFormat format, TextureDataType typeData, TextureType type);
        Texture(uint32_t texture, uint64_t handle, TextureFormat format, TextureDataType typeData, TextureType type);
        Texture(const Texture& texture);
        Texture(Texture&& texture) noexcept;
        ~Texture();

        Texture& operator=(const Texture& texture);
        Texture& operator=(Texture&& texture) noexcept;

        void setSubData(int level, int xoffset, int yoffset, int width, int height, const void* data);

        void bind();
        void unbind();
        void destroy();

        uint32_t getTexture() const;
        uint64_t getHandle() const;

    private:
        uint32_t texture;
        uint64_t handle;
        TextureFormat format;
        TextureDataType typeData;
        TextureType type;
    };
}