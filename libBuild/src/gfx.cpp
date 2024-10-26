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
}