#include "buffers/vao.hpp"
#include <glad/glad.h>
#include <lc.hpp>

namespace gfx {
    VAO::VAO()
    {
        glGenVertexArrays(1, &vao);
        bind();
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &vao);
    }

    void VAO::bind()
    {
        glBindVertexArray(vao);
    }
} // namespace gfx
