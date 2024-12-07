#include "buffers/texture.hpp"
#include <glad/glad.h>
#include "imageio.hpp"
#include <lc.hpp>
#include "gfx.hpp"
#include "texturebuilder.hpp"

namespace gfx
{
    Texture::Texture()
        : texture(0), handle(0), format(TextureFormat::RGBA), typeData(TextureDataType::UNSIGNED_BYTE), type(TextureType::TEXTURE_2D)
    {
    }

    Texture::Texture(uint32_t texture, TextureFormat format, TextureDataType typeData, TextureType type)
        : texture(texture), handle(0), format(format), typeData(typeData), type(type)
    {
    }

    Texture::Texture(uint32_t texture, uint64_t handle, TextureFormat format, TextureDataType typeData, TextureType type)
        : texture(texture), handle(handle), format(format), typeData(typeData), type(type)
    {
    }

    Texture::Texture(const Texture& texture)
        : texture(texture.texture), handle(texture.handle), format(texture.format), type(texture.type)
    {
    }

    Texture::Texture(Texture&& texture) noexcept
        : texture(texture.texture), handle(texture.handle), format(texture.format), type(texture.type)
    {
        texture.texture = 0;
        texture.handle = 0;
    }

    Texture::~Texture()
    {
        destroy();
    }

    Texture& Texture::operator=(const Texture& texture)
    {
        if(this != &texture)
        {
            this->texture = texture.texture;
            this->handle = texture.handle;
            this->format = texture.format;
            this->type = texture.type;
        }

        return *this;
    }

    Texture& Texture::operator=(Texture&& texture) noexcept
    {
        if(this != &texture)
        {
            this->texture = texture.texture;
            this->handle = texture.handle;
            this->format = texture.format;
            this->type = texture.type;

            texture.texture = 0;
            texture.handle = 0;
        }

        return *this;
    }

    void Texture::setSubData(int level, int xoffset, int yoffset, int width, int height, const void* data)
    {
        glTexSubImage2D(GetType(type), level, xoffset, yoffset, width, height, GetFormat(format), GetTextureDataType(typeData), data);
    }

    void Texture::bind()
    {
        if(gfx::GetTextureBindingMode() == TextureBindingMode::BINDLESS)
        {
            lc::Log<gfx::GL>("WARNING", "Cannot bind texture in bindless mode");
            return;
        }

        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void Texture::unbind()
    {
        if(gfx::GetTextureBindingMode() == TextureBindingMode::BINDLESS)
        {
            lc::Log<gfx::GL>("WARNING", "Cannot bind texture in bindless mode");
            return;
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::destroy()
    {
        if(texture != 0)
            glDeleteTextures(1, &texture);
        texture = 0;
    }

    uint32_t Texture::getTexture() const
    {
        return texture;
    }

    uint64_t Texture::getHandle() const
    {
        return handle;
    }
}