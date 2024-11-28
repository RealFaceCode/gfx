#include "buffers/texture.hpp"
#include <glad/glad.h>
#include "imageload.hpp"

namespace gfx
{
    Texture::Texture()
    : texture(0), image()
    {}

    Texture::Texture(const Image& image)
    : texture(0), image(std::make_shared<Image>(image))
    {}

    Texture::Texture(const std::string& path)
    : texture(0)
    {
        auto loadedImage = LoadImageFromFile(path);
        image = std::make_shared<Image>(loadedImage);
    }

    Texture::Texture(const Texture& other)
    : texture(other.texture), image(other.image)
    {}

    Texture::Texture(Texture&& other)
    : texture(other.texture), image(std::move(other.image))
    {}

    Texture& Texture::operator=(Texture&& other)
    {
        texture = other.texture;
        image = std::move(other.image);
        return *this;
    }

    Texture::~Texture()
    {
        if (texture != 0)
            glDeleteTextures(1, &texture);
    }

    void Texture::build()
    {
        if (texture == 0)
            glGenTextures(1, &texture);
        bind();
        
        auto size = image->getSize();
        auto channels = image->getChannels();
        auto data = image->getData();

        GLenum format = GL_RGB;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(wrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(wrapT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(magFilter));

        glGenerateMipmap(GL_TEXTURE_2D);
        
        unbind();
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::setParameter(uint32_t pname, int param)
    {
        bind();
        glTexParameteri(GL_TEXTURE_2D, pname, param);
        unbind();
    }

    void Texture::setParameter(uint32_t pname, float param)
    {
        bind();
        glTexParameterf(GL_TEXTURE_2D, pname, param);
        unbind();
    }

    void Texture::setWrapS(TextureWrap param)
    {
        wrapS = param;
        setParameter(GL_TEXTURE_WRAP_S, static_cast<int>(param));
    }

    void Texture::setWrapT(TextureWrap param)
    {
        wrapT = param;
        setParameter(GL_TEXTURE_WRAP_T, static_cast<int>(param));
    }

    void Texture::setWrapR(TextureWrap param)
    {
        wrapR = param;
        setParameter(GL_TEXTURE_WRAP_R, static_cast<int>(param));
    }

    void Texture::setMinFilter(TextureMinMagFilter param)
    {
        minFilter = param;
        setParameter(GL_TEXTURE_MIN_FILTER, static_cast<int>(param));
    }

    void Texture::setMagFilter(TextureMinMagFilter param)
    {
        magFilter = param;
        setParameter(GL_TEXTURE_MAG_FILTER, static_cast<int>(param));
    }

    void Texture::setAnisotropy(float param)
    {
        bind();
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, param);
        unbind();
    }

    const uint32_t& Texture::getTextureID() const
    {
        return texture;
    }

    const Image& Texture::getImage() const
    {
        return *image;
    }
}