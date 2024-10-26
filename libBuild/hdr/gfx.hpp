#pragma once

#include "defines.hpp"

typedef void *(*loadproc)(const char *name);

namespace gfx
{
    bool GFX_API Init(loadproc);
    void GFX_API DeInit();
    void GFX_API clear();
}