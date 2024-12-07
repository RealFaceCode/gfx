#pragma once

#include "defines.hpp"
#include "buffers/texture.hpp"

namespace gfx
{
    enum class WrapMode
    {
        REPEAT = 0,
        MIRRORED_REPEAT = 1,
        CLAMP_TO_EDGE = 2,
        CLAMP_TO_BORDER = 3
    };

    enum class FilterMode
    {
        NEAREST = 0,
        LINEAR = 1,
        NEAREST_MIPMAP_NEAREST = 2,
        LINEAR_MIPMAP_NEAREST = 3,
        NEAREST_MIPMAP_LINEAR = 4,
        LINEAR_MIPMAP_LINEAR = 5
    };

    enum class TextureFormat
    {
        RED = 0,
        RG = 1,
        RGB = 2,
        BGR = 3,
        RGBA = 4,
        BGRA = 5,
        RED_INTEGER = 6,
        RG_INTEGER = 7,
        RGB_INTEGER = 8,
        BGR_INTEGER = 9,
        RGBA_INTEGER = 10,
        BGRA_INTEGER = 11,
        STENCIL_INDEX = 12,
        DEPTH_COMPONENT = 13,
        DEPTH_STENCIL = 14
    };

    enum class TextureType
    {
        TEXTURE_1D,
        TEXTURE_2D,
        TEXTURE_3D,
        TEXTURE_1D_ARRAY,
        TEXTURE_2D_ARRAY,
        TEXTURE_RECTANGLE,
        TEXTURE_CUBE_MAP,
        TEXTURE_CUBE_MAP_ARRAY,
        TEXTURE_BUFFER,
        TEXTURE_2D_MULTISAMPLE,
        TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    enum class TextureDataType
    {
        UNSIGNED_BYTE,
        BYTE,
        UNSIGNED_SHORT,
        SHORT,
        UNSIGNED_INT,
        INT,
        FLOAT,
        UNSIGNED_BYTE_3_3_2,
        UNSIGNED_BYTE_2_3_3_REV,
        UNSIGNED_SHORT_5_6_5,
        UNSIGNED_SHORT_5_6_5_REV,
        UNSIGNED_SHORT_4_4_4_4,
        UNSIGNED_SHORT_4_4_4_4_REV,
        UNSIGNED_SHORT_5_5_5_1,
        UNSIGNED_SHORT_1_5_5_5_REV,
        UNSIGNED_INT_8_8_8_8,
        UNSIGNED_INT_8_8_8_8_REV,
        UNSIGNED_INT_10_10_10_2,
        UNSIGNED_INT_2_10_10_10_REV,
    };

    GFX_API unsigned int GetWrapMode(WrapMode wrapMode);
    GFX_API unsigned int GetFilterMode(FilterMode filterMode);
    GFX_API unsigned int GetFormat(TextureFormat format);
    GFX_API unsigned int GetType(TextureType type);
    GFX_API unsigned int GetTextureDataType(TextureDataType type);

    class GFX_API TextureBuilder
    {
    public:
        TextureBuilder();
        TextureBuilder(const TextureBuilder&) = delete;
        TextureBuilder& operator=(const TextureBuilder&) = delete;
        TextureBuilder(TextureBuilder&&) = delete;
        TextureBuilder& operator=(TextureBuilder&&) = delete;

        TextureBuilder& setWrapModeS(WrapMode wrapMode);
        TextureBuilder& setWrapModeT(WrapMode wrapMode);
        TextureBuilder& setWrapModeR(WrapMode wrapMode);
        TextureBuilder& setFilterModeMin(FilterMode filterMode);
        TextureBuilder& setFilterModeMag(FilterMode filterMode);
        TextureBuilder& setFormat(TextureFormat format);
        TextureBuilder& setFormatInner(TextureFormat type);
        TextureBuilder& setDataType(TextureDataType dataType);
        TextureBuilder& setType(TextureType type);

        WrapMode getWrapModeS() const;
        WrapMode getWrapModeT() const;
        WrapMode getWrapModeR() const;
        FilterMode getFilterModeMin() const;
        FilterMode getFilterModeMag() const;
        TextureFormat getFormat() const;
        TextureFormat getFormatInner() const;
        TextureDataType getDataType() const;
        TextureType getType() const;

        Texture build(uint32_t width, uint32_t height);
        Texture build(const void* data, int width, int height);
        Texture build(std::string_view path);

    private:
        WrapMode wrapModeS;
        WrapMode wrapModeT;
        WrapMode wrapModeR;
        FilterMode filterModeMin;
        FilterMode filterModeMag;
        TextureFormat format;
        TextureFormat formatInner;
        TextureDataType dataType;
        TextureType type;

        unsigned int texture;
    };
}
