#pragma once

#include "defines.hpp"
#include <cstdint>	

typedef void *(*loadproc)(const char *name);

namespace gfx
{
    GFX_API bool Init(loadproc, TextureBindingMode = TextureBindingMode::BIND);
    GFX_API void DeInit();
    GFX_API void Clear();
    GFX_API void PrintVRVOpenGL();
    GFX_API void PrintSupportedOpenGLFeatures();
    GFX_API bool CheckSupoortedOpenGLFeature(const char*);
    GFX_API void WireFrameMode(bool);
    GFX_API void SetTextureBindingMode(TextureBindingMode);
    GFX_API TextureBindingMode GetTextureBindingMode();
    GFX_API uint64_t GetMaxUBOSiumultaneousBindings();
}