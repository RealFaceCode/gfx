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

    enum class TextureFormat
    {
        RED = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA,
        DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
        DEPTH_STENCIL = GL_DEPTH_STENCIL
    };

    enum class TextureType
    {
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        BYTE = GL_BYTE,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        SHORT = GL_SHORT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        INT = GL_INT,
        FLOAT = GL_FLOAT,
        UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
        UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
        UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
        UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
        UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
        UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
        UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
        UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
        UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
        UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
        UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
        UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
    };

    enum class TextureInternalFormat
    {
        R8 = GL_R8,
        R8_SNORM = GL_R8_SNORM,
        R16 = GL_R16,
        R16_SNORM = GL_R16_SNORM,
        RG8 = GL_RG8,
        RG8_SNORM = GL_RG8_SNORM,
        RG16 = GL_RG16,
        RG16_SNORM = GL_RG16_SNORM,
        R3_G3_B2 = GL_R3_G3_B2,
        RGB4 = GL_RGB4,
        RGB5 = GL_RGB5,
        RGB8 = GL_RGB8,
        RGB8_SNORM = GL_RGB8_SNORM,
        RGB10 = GL_RGB10,
        RGB12 = GL_RGB12,
        RGB16 = GL_RGB16,
        RGB16_SNORM = GL_RGB16_SNORM,
        RGBA2 = GL_RGBA2,
        RGBA4 = GL_RGBA4,
        RGB5_A1 = GL_RGB5_A1,
        RGBA8 = GL_RGBA8,
        RGBA8_SNORM = GL_RGBA8_SNORM,
        RGB10_A2 = GL_RGB10_A2,
        RGB10_A2UI = GL_RGB10_A2UI,
        RGBA12 = GL_RGBA12,
        RGBA16 = GL_RGBA16,
        SRGB8 = GL_SRGB8,
        SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
        R16F = GL_R16F,
        RG16F = GL_RG16F,
        RGB16F = GL_RGB16F,
        RGBA16F = GL_RGBA16F,
        R32F = GL_R32F,
        RG32F = GL_RG32F,
        RGB32F = GL_RGB32F,
        RGBA32F = GL_RGBA32F,
        R11F_G11F_B10F = GL_R11F_G11F_B10F,
        RGB9_E5 = GL_RGB9_E5,
        R8I = GL_R8I,
        R8UI = GL_R8UI,
        R16I = GL_R16I,
        R16UI = GL_R16UI,
        R32I = GL_R32I,
        R32UI = GL_R32UI,
        RG8I = GL_RG8I,
        RG8UI = GL_RG8UI,
        RG16I = GL_RG16I,
        RG16UI = GL_RG16
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
        void makeResident();
        void makeNonResident();
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

        uint32_t getTextureID() const;
        uint64_t getTextureHandle() const;

    private:

        TextureWrap wrapS = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapT = TextureWrap::CLAMP_TO_EDGE;
        TextureWrap wrapR = TextureWrap::CLAMP_TO_EDGE;
        TextureMinMagFilter minFilter = TextureMinMagFilter::LINEAR_MIPMAP_LINEAR;
        TextureMinMagFilter magFilter = TextureMinMagFilter::LINEAR;
        float anisotropy = 1.0f;

        uint32_t texture;
        uint64_t handle;

        static TextureBindingMode bindingMode;;
    };
}