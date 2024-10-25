#include "gfx.hpp"
#include <glad/glad.h>
#include <lc.hpp>

namespace gfx
{
    bool Init()
    {
        return gladLoadGL();
    }

    void DeInit()
    {}
}