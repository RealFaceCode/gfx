#include "texturebuilder.hpp"
#include "gfx.hpp"
#include "imageio.hpp"

namespace gfx
{
    unsigned int GetWrapMode(WrapMode wrapMode)
    {
        switch(wrapMode)
        {
        using enum gfx::WrapMode;
        case REPEAT:                        return GL_REPEAT;
        case MIRRORED_REPEAT:               return GL_MIRRORED_REPEAT;
        case CLAMP_TO_EDGE:                 return GL_CLAMP_TO_EDGE;
        case CLAMP_TO_BORDER:               return GL_CLAMP_TO_BORDER;
        }
    }

    unsigned int GetFilterMode(FilterMode filterMode)
    {
        switch(filterMode)
        {
        using enum gfx::FilterMode;
        case NEAREST:                       return GL_NEAREST;
        case LINEAR:                        return GL_LINEAR;
        case NEAREST_MIPMAP_NEAREST:        return GL_NEAREST_MIPMAP_NEAREST;
        case LINEAR_MIPMAP_NEAREST:         return GL_LINEAR_MIPMAP_NEAREST;
        case NEAREST_MIPMAP_LINEAR:         return GL_NEAREST_MIPMAP_LINEAR;
        case LINEAR_MIPMAP_LINEAR:          return GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    unsigned int GetFormat(TextureFormat format)
    {
        switch(format)
        {
        using enum gfx::TextureFormat;
        case RED:                           return GL_RED;
        case RG:                            return GL_RG;
        case RGB:                           return GL_RGB;
        case BGR:                           return GL_BGR;
        case RGBA:                          return GL_RGBA;
        case BGRA:                          return GL_BGRA;
        case RED_INTEGER:                   return GL_RED_INTEGER;
        case RG_INTEGER:                    return GL_RG_INTEGER;
        case RGB_INTEGER:                   return GL_RGB_INTEGER;
        case BGR_INTEGER:                   return GL_BGR_INTEGER;
        case RGBA_INTEGER:                  return GL_RGBA_INTEGER;
        case BGRA_INTEGER:                  return GL_BGRA_INTEGER;
        case STENCIL_INDEX:                 return GL_STENCIL_INDEX;
        case DEPTH_COMPONENT:               return GL_DEPTH_COMPONENT;
        case DEPTH_STENCIL:                 return GL_DEPTH_STENCIL;
        }
    }

    unsigned int GetType(TextureType type)
    {
        switch(type)
        {
        using enum gfx::TextureType;
        case TEXTURE_1D:                    return GL_TEXTURE_1D;
        case TEXTURE_2D:                    return GL_TEXTURE_2D;
        case TEXTURE_3D:                    return GL_TEXTURE_3D;
        case TEXTURE_1D_ARRAY:              return GL_TEXTURE_1D_ARRAY;
        case TEXTURE_2D_ARRAY:              return GL_TEXTURE_2D_ARRAY;
        case TEXTURE_RECTANGLE:             return GL_TEXTURE_RECTANGLE;
        case TEXTURE_CUBE_MAP:              return GL_TEXTURE_CUBE_MAP;
        case TEXTURE_CUBE_MAP_ARRAY:        return GL_TEXTURE_CUBE_MAP_ARRAY;
        case TEXTURE_BUFFER:                return GL_TEXTURE_BUFFER;
        case TEXTURE_2D_MULTISAMPLE:        return GL_TEXTURE_2D_MULTISAMPLE;
        case TEXTURE_2D_MULTISAMPLE_ARRAY:  return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
        }
    }

    unsigned int GetTextureDataType(TextureDataType type)
    {
        switch(type)
        {
        using enum gfx::TextureDataType;
        case UNSIGNED_BYTE:                 return GL_UNSIGNED_BYTE;
        case BYTE:                          return GL_BYTE;
        case UNSIGNED_SHORT:                return GL_UNSIGNED_SHORT;
        case SHORT:                         return GL_SHORT;
        case UNSIGNED_INT:                  return GL_UNSIGNED_INT;
        case INT:                           return GL_INT;
        case FLOAT:                         return GL_FLOAT;
        case UNSIGNED_BYTE_3_3_2:           return GL_UNSIGNED_BYTE_3_3_2;
        case UNSIGNED_BYTE_2_3_3_REV:       return GL_UNSIGNED_BYTE_2_3_3_REV;
        case UNSIGNED_SHORT_5_6_5:          return GL_UNSIGNED_SHORT_5_6_5;
        case UNSIGNED_SHORT_5_6_5_REV:      return GL_UNSIGNED_SHORT_5_6_5_REV;
        case UNSIGNED_SHORT_4_4_4_4:        return GL_UNSIGNED_SHORT_4_4_4_4;
        case UNSIGNED_SHORT_4_4_4_4_REV:    return GL_UNSIGNED_SHORT_4_4_4_4_REV;
        case UNSIGNED_SHORT_5_5_5_1:        return GL_UNSIGNED_SHORT_5_5_5_1;
        case UNSIGNED_SHORT_1_5_5_5_REV:    return GL_UNSIGNED_SHORT_1_5_5_5_REV;
        case UNSIGNED_INT_8_8_8_8:          return GL_UNSIGNED_INT_8_8_8_8;
        case UNSIGNED_INT_8_8_8_8_REV:      return GL_UNSIGNED_INT_8_8_8_8_REV;
        case UNSIGNED_INT_10_10_10_2:       return GL_UNSIGNED_INT_10_10_10_2;
        case UNSIGNED_INT_2_10_10_10_REV:   return GL_UNSIGNED_INT_2_10_10_10_REV;
        }
    }

    TextureBuilder::TextureBuilder()
    {
        wrapModeS = WrapMode::REPEAT;
        wrapModeT = WrapMode::REPEAT;
        wrapModeR = WrapMode::REPEAT;
        filterModeMin = FilterMode::LINEAR;
        filterModeMag = FilterMode::LINEAR;
        format = TextureFormat::RGB;
        formatInner = TextureFormat::RGB;
        dataType = TextureDataType::UNSIGNED_BYTE;
        type = TextureType::TEXTURE_2D;
    }

    TextureBuilder& TextureBuilder::setWrapModeS(WrapMode wrapMode) {
        wrapModeS = wrapMode;
        return *this;
    }

    TextureBuilder& TextureBuilder::setWrapModeT(WrapMode wrapMode) {
        wrapModeT = wrapMode;
        return *this;
    }

    TextureBuilder& TextureBuilder::setWrapModeR(WrapMode wrapMode) {
        wrapModeR = wrapMode;
        return *this;
    }

    TextureBuilder& TextureBuilder::setFilterModeMin(FilterMode filterMode) {
        filterModeMin = filterMode;
        return *this;
    }

    TextureBuilder& TextureBuilder::setFilterModeMag(FilterMode filterMode) {
        filterModeMag = filterMode;
        return *this;
    }

    TextureBuilder& TextureBuilder::setFormat(TextureFormat format) {
        this->format = format;
        return *this;
    }

    TextureBuilder& TextureBuilder::setFormatInner(TextureFormat formatInner) {
        this->formatInner = formatInner;
        return *this;
    }

    TextureBuilder& TextureBuilder::setDataType(TextureDataType dataType) {
        this->dataType = dataType;
        return *this;
    }

    TextureBuilder& TextureBuilder::setType(TextureType type) {
        this->type = type;
        return *this;
    }

    WrapMode TextureBuilder::getWrapModeS() const {
        return wrapModeS;
    }

    WrapMode TextureBuilder::getWrapModeT() const {
        return wrapModeT;
    }

    WrapMode TextureBuilder::getWrapModeR() const {
        return wrapModeR;
    }

    FilterMode TextureBuilder::getFilterModeMin() const {
        return filterModeMin;
    }

    FilterMode TextureBuilder::getFilterModeMag() const {
        return filterModeMag;
    }

    TextureFormat TextureBuilder::getFormat() const {
        return format;
    }

    TextureFormat TextureBuilder::getFormatInner() const {
        return formatInner;
    }

    TextureDataType TextureBuilder::getDataType() const {
        return dataType;
    }

    TextureType TextureBuilder::getType() const {
        return type;
    }

    Texture TextureBuilder::build(uint32_t width, uint32_t height)
    {
        glGenTextures(1, &texture);
        auto t = GetType(type); GL_TEXTURE_2D;
        glBindTexture(t, texture);

        auto ws = GetWrapMode(wrapModeS);
        auto wt = GetWrapMode(wrapModeT);
        auto wr = GetWrapMode(wrapModeR);

        glTexParameteri(t, GL_TEXTURE_WRAP_S, ws);
        glTexParameteri(t, GL_TEXTURE_WRAP_T, wr);
        glTexParameteri(t, GL_TEXTURE_WRAP_R, wt);

        auto min = GetFilterMode(filterModeMin);
        auto mag = GetFilterMode(filterModeMag);

        glTexParameteri(t, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(t, GL_TEXTURE_MAG_FILTER, mag);

        auto f = GetFormat(format);
        auto fi = GetFormat(formatInner);
        auto d = GetTextureDataType(dataType);

        glTexImage2D(t, 0, f, width, height, 0, fi, d, nullptr);

        if(gfx::GetTextureBindingMode() == gfx::TextureBindingMode::BINDLESS)
        {
            auto handle = glGetTextureHandleARB(texture);
            glMakeTextureHandleResidentARB(handle);
            return Texture(texture, handle, format, dataType, type);
        }

        return Texture(texture, format, dataType, type);

    }

    Texture TextureBuilder::build(const void *data, int width, int height)
    {
        // Implementation for building texture from data
        glGenTextures(1, &texture);
        glBindTexture(GetType(type), texture);

        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_S, GetWrapMode(wrapModeS));
        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_T, GetWrapMode(wrapModeT));
        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_R, GetWrapMode(wrapModeR));

        glTexParameteri(GetType(type), GL_TEXTURE_MIN_FILTER, GetFilterMode(filterModeMin));
        glTexParameteri(GetType(type), GL_TEXTURE_MAG_FILTER, GetFilterMode(filterModeMag));

        glTexImage2D(GetType(type), 0, GetFormat(format), width, height, 0, GetFormat(formatInner), GetTextureDataType(dataType), data);

        if(gfx::GetTextureBindingMode() == gfx::TextureBindingMode::BINDLESS)
        {
            auto handle = glGetTextureHandleARB(texture);
            glMakeTextureHandleResidentARB(handle);
            return Texture(texture, glGetTextureHandleARB(texture), format, dataType, type);
        }

        return Texture(texture, format, dataType, type);
    }

    Texture TextureBuilder::build(std::string_view path)
    {
        // Implementation for building texture from file
        auto image = LoadAsImage(std::string(path));
        if(image.data == nullptr)
            return Texture();

        glGenTextures(1, &texture);
        glBindTexture(GetType(type), texture);

        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_S, GetWrapMode(wrapModeS));
        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_T, GetWrapMode(wrapModeT));
        glTexParameteri(GetType(type), GL_TEXTURE_WRAP_R, GetWrapMode(wrapModeR));

        glTexParameteri(GetType(type), GL_TEXTURE_MIN_FILTER, GetFilterMode(filterModeMin));
        glTexParameteri(GetType(type), GL_TEXTURE_MAG_FILTER, GetFilterMode(filterModeMag));

        glTexImage2D(GetType(type), 0, GetFormat(format), image.width, image.height, 0, GetFormat(formatInner), GetTextureDataType(dataType), image.data);

        if(gfx::GetTextureBindingMode() == gfx::TextureBindingMode::BINDLESS)
        {
            auto handle = glGetTextureHandleARB(texture);
            glMakeTextureHandleResidentARB(handle);
            return Texture(texture, glGetTextureHandleARB(texture), format, dataType, type);
        }
        
        return Texture(texture, format, dataType, type);
    }
}