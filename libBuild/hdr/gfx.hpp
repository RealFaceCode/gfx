#pragma once

#include "defines.hpp"

typedef void *(*loadproc)(const char *name);

namespace gfx
{
    bool GFX_API Init(loadproc);
    void GFX_API DeInit();
    void GFX_API Clear();
    void GFX_API PrintVRVOpenGL();
    void GFX_API PrintSupportedOpenGLFeatures();
    void GFX_API WireFrameMode(bool);
}