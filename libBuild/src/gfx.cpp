#include "gfx.hpp"
#include <glad/glad.h>
#include <lc.hpp>

namespace gfx
{
    bool Init(loadproc getProcAddress)
    {
        auto load = gladLoadGLLoader(getProcAddress);
        return load;
    }

    void DeInit()
    {}

    void clear()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void printVRVOpenGL()
    {
        std::string glVendor((const char*)glGetString(GL_VENDOR));
        std::string glRenderer((const char*)glGetString(GL_RENDERER));
        std::string glVersion((const char*)glGetString(GL_VERSION));
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Vendor: {}", glVendor);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Renderer: {}", glRenderer);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Version: {}", glVersion);
    }
}