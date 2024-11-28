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

    void Clear()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void PrintVRVOpenGL()
    {
        std::string glVendor((const char*)glGetString(GL_VENDOR));
        std::string glRenderer((const char*)glGetString(GL_RENDERER));
        std::string glVersion((const char*)glGetString(GL_VERSION));
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Vendor: {}", glVendor);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Renderer: {}", glRenderer);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Version: {}", glVersion);
    }

    void PrintSupportedOpenGLFeatures()
    {
        GLint numExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Extensions: {}", numExtensions);
        for (int i = 0; i < numExtensions; i++)
        {
            lc::Log<"GFX BUILD">("DEBUG", "OpenGL Extension: {}", (const char*)glGetStringi(GL_EXTENSIONS, i));
        }
    }

    bool CheckSupoortedOpenGLFeature(const char* feature)
    {
        GLint numExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++)
        {
            if (strcmp((const char*)glGetStringi(GL_EXTENSIONS, i), feature) == 0)
                return true;
        }
        return false;
    }

    void WireFrameMode(bool mode)
    {
        if (mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}