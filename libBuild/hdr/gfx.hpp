#pragma once

#include "defines.hpp"
#include <cstdint>	

typedef void *(*loadproc)(const char *name);

namespace gfx
{
    GFX_API bool Init(loadproc, TextureBindingMode = TextureBindingMode::BIND);
    GFX_API void DeInit();
    GFX_API void Clear(float r, float g, float b, float a, int clearFlags);
    GFX_API void PrintVRVOpenGL();
    GFX_API void PrintSupportedOpenGLFeatures();
    GFX_API bool CheckSupoortedOpenGLFeature(const char* feature);
    GFX_API void WireFrameMode(bool wireframe);
    GFX_API void SetTextureBindingMode(TextureBindingMode mode);
    GFX_API TextureBindingMode GetTextureBindingMode();
    GFX_API uint64_t GetMaxUBOSiumultaneousBindings();

    GFX_API void EnableDepthTest(int depthTestFuncFlag);
    GFX_API void DisableDepthTest();
    GFX_API void EnableBlend(int blend, int blendFuncFlag);
    GFX_API void DisableBlend();
    GFX_API void EnableFaceCulling(int cullFace, int frontFace);
    GFX_API void DisableFaceCulling();
    GFX_API void EnableStencilTest(int stencilTest, int stencilFuncFlag, int stencilOpFlag);
    GFX_API void DisableStencilTest();
}