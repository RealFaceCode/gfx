#include "buffers/texture.hpp"
#include <glad/glad.h>
#include "imageio.hpp"
#include <lc.hpp>
#include "gfx.hpp"

namespace gfx
{
    TextureBindingMode Texture::bindingMode = TextureBindingMode::NONE;

    Texture::Texture()
    : texture(0)
    {
        if(bindingMode == TextureBindingMode::NONE)
            bindingMode = GetTextureBindingMode();
    }

    Texture::Texture(const Image& image)
    : Texture()
    {
        build(image);
    }

    Texture::Texture(const std::string& path, bool flip)
    : Texture()
    {
        build(path, flip);
    }

    Texture::Texture(const unsigned char* data, int width, int height, int channels, bool flip)
    : Texture()
    {
        bild(data, width, height, channels, flip);
    }

    Texture::Texture(const Texture& other)
    : texture(other.texture), handle(other.handle)
    {}

    Texture::Texture(Texture&& other)
    : texture(other.texture), handle(other.handle)
    {}

    Texture& Texture::operator=(Texture&& other)
    {
        texture = other.texture;
        handle = other.handle;
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
        glBindTexture(GL_TEXTURE_2D, texture);

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

        auto format = GL_RGBA;
        if (image.channels == 1)
            format = GL_RED;
        else if (image.channels == 2)
            format = GL_RG;
        else if (image.channels == 3)
            format = GL_RGB;
        

        glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        if(bindingMode == TextureBindingMode::BINDLESS)
        {
            handle = glGetTextureHandleARB(texture);
            glMakeTextureHandleResidentARB(handle);
        }
    }

    void Texture::build(const std::string& path, bool flip)
    {
        build(LoadAsImage(path, flip));
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

    void Texture::makeResident()
    {
        if(bindingMode == TextureBindingMode::BINDLESS)
        {
            glMakeTextureHandleResidentARB(handle);
            return;
        }
        lc::Log<GFX>("WARNING", "Cannot make texture resident in non-bindless mode.");
    }

    void Texture::makeNonResident()
    {
        if(bindingMode == TextureBindingMode::BINDLESS)
        {
            glMakeTextureHandleNonResidentARB(handle);
            return;
        }
        lc::Log<GFX>("WARNING", "Cannot make texture non-resident in non-bindless mode.");
    }

    void Texture::bind()
    {
        if(bindingMode == TextureBindingMode::BINDLESS)
        {
            lc::Log<GFX>("WARNING", "Cannot bind texture in bindless mode.");
            return;
        }

        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void Texture::unbind()
    {
        if(bindingMode == TextureBindingMode::BINDLESS)
        {
            lc::Log<GFX>("WARNING", "Cannot unbind texture in bindless mode.");
            return;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //TODO: remove this and write Texture bilder class
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

    uint32_t Texture::getTextureID() const
    {
        return texture;
    }

    uint64_t Texture::getTextureHandle() const
    {
        return handle;
    }
}