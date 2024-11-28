#include "buffers/texture.hpp"
#include <glad/glad.h>
#include "imageio.hpp"
#include <lc.hpp>

namespace gfx
{
    Texture::Texture()
    : texture(0)
    {}

    Texture::Texture(const Image& image)
    : texture(0)
    {
        build(image);
    }

    Texture::Texture(const std::string& path, bool flip)
    : texture(0)
    {
        build(path, flip);
    }

    Texture::Texture(const unsigned char* data, int width, int height, int channels, bool flip)
    : texture(0)
    {
        bild(data, width, height, channels, flip);
    }

    Texture::Texture(const Texture& other)
    : texture(other.texture)
    {}

    Texture::Texture(Texture&& other)
    : texture(other.texture)
    {}

    Texture& Texture::operator=(Texture&& other)
    {
        texture = other.texture;
        return *this;
    }

    Texture::~Texture()
    {
        if (texture != 0)
            glDeleteTextures(1, &texture);
    }

    void Texture::build(const Image& image)
    {
        glGenTextures(1, &texture);
        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(wrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(wrapT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, static_cast<int>(wrapR));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(magFilter));

        float maxAnisotropy = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
        if (anisotropy > maxAnisotropy)
        {
            anisotropy = maxAnisotropy;
            lc::Log<GFX>("WARNING", "Anisotropy value is greater than the maximum anisotropy value supported by the system. Setting anisotropy to the maximum value supported by the system.");
        }
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        unbind();
    }

    void Texture::build(const std::string& path, bool flip)
    {
        auto loadedImage = LoadAsImage(path, flip);
        build(loadedImage);
    }

    void Texture::bild(const unsigned char* data, int width, int height, int channels, bool flip)
    {
        Image image;
        image.data = const_cast<unsigned char*>(data);
        image.width = width;
        image.height = height;
        image.channels = channels;
        build(image);
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
        anisotropy = param;
    }

    const uint32_t& Texture::getTextureID() const
    {
        return texture;
    }
}