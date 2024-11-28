#pragma once

#include "defines.hpp"
#include <string>
#include <glad/glad.h>
#include "image.hpp"
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

    class GFX_API Texture
    {
    public:
        Texture();
        Texture(const Image& image);
        Texture(const std::string& path);
        Texture(const Texture& other);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        ~Texture();

        void build();
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
        const Image& getImage() const;

    private:
        TextureWrap wrapS = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapT = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapR = TextureWrap::CLAMP_TO_EDGE;
        TextureMinMagFilter minFilter = TextureMinMagFilter::LINEAR;
        TextureMinMagFilter magFilter = TextureMinMagFilter::LINEAR;

        uint32_t texture;
        std::shared_ptr<Image> image;
    };
}