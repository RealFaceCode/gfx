#pragma once

#include "defines.hpp"
#include <string>
#include <glad/glad.h>
#include <memory>

namespace gfx
{

    enum class TextureWrap
    {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
    };

    enum class TextureMinMagFilter
    {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,
        NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
    };

    struct Image;

    class GFX_API Texture
    {
    public:
        Texture();
        Texture(const Image& image);
        Texture(const std::string& path, bool flip = true);
        Texture(const unsigned char* data, int width, int height, int channels, bool flip = true);
        Texture(const Texture& other);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        ~Texture();

        void build(const Image& image);
        void build(const std::string& path, bool flip = true);
        void bild(const unsigned char* data, int width, int height, int channels, bool flip = true);
        void bind();
        void unbind();

        void setParameter(uint32_t pname, int param);
        void setParameter(uint32_t pname, float param);

        void setWrapS(TextureWrap param);
        void setWrapT(TextureWrap param);
        void setWrapR(TextureWrap param);

        void setMinFilter(TextureMinMagFilter param);
        void setMagFilter(TextureMinMagFilter param);

        void setAnisotropy(float param);

        const uint32_t& getTextureID() const;

    private:

        TextureWrap wrapS = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapT = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapR = TextureWrap::CLAMP_TO_EDGE;
        TextureMinMagFilter minFilter = TextureMinMagFilter::LINEAR_MIPMAP_LINEAR;
        TextureMinMagFilter magFilter = TextureMinMagFilter::LINEAR;
        float anisotropy = 1.0f;

        uint32_t texture;
    };
}