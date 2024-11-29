#pragma once

#define GFX_VERSION_MAJOR 0
#define GFX_VERSION_MINOR 1
#define GFX_VERSION_PATCH 0

#ifdef _WIN32
        #define DLL_EXPORT __declspec(dllexport)
        #define DLL_IMPORT __declspec(dllimport)
#else
        #define DLL_EXPORT __attribute__((visibility("default")))
        #define DLL_IMPORT __attribute__((visibility("default")))
#endif

#ifdef GFX_EXPORTS
    #define GFX_API DLL_EXPORT
#else
    #define GFX_API DLL_IMPORT
#endif

namespace gfx
{
    constexpr const char GFX[] = "GFX BUILD";
    constexpr const char GL[] = "OPENGL";
    constexpr const char BINDLES_TEXTURE[] = "GL_ARB_bindless_texture";

    enum class TextureBindingMode
    {
        BINDLESS,
        BIND,
        NONE
    };
}