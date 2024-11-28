#pragma once

#include "defines.hpp"

typedef void *(*loadproc)(const char *name);

namespace gfx
{
    GFX_API bool Init(loadproc);
    GFX_API void DeInit();
    GFX_API void Clear();
    GFX_API void PrintVRVOpenGL();
    GFX_API void PrintSupportedOpenGLFeatures();
    GFX_API bool CheckSupoortedOpenGLFeature(const char*);
    GFX_API void WireFrameMode(bool);
}