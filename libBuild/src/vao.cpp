#include "vao.hpp"
#include <glad/glad.h>
#include <lc.hpp>

namespace gfx {

    VAO::VAO()
    {
        glGenVertexArrays(1, &vao);
        glBindBuffer(GL_ARRAY_BUFFER, vao);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &vao);
    }

    void VAO::bind()
    {
        glBindVertexArray(vao);
    }

    void VAO::addAttribute(int size, unsigned int type, bool normalized, int stride, void* pointer)
    {
        attributes.emplace_back(VertexArrayAttribute(attributes.size(), size, type, normalized, stride, pointer));
    }

    void VAO::addAttribute(int size, unsigned int type, bool normalized, int stride, void* pointer, unsigned int indexVBO, unsigned int typeVBO)
    {
        attributes.emplace_back(VertexArrayAttribute(attributes.size(), size, type, normalized, stride, pointer, indexVBO, typeVBO));
    }

    void VAO::build()
    {
        bind();
        for(auto& attribute : attributes)
        {
            if(attribute.indexVBO != -1)
                glBindBuffer(attribute.typeVBO, attribute.indexVBO);
                
            glEnableVertexAttribArray(attribute.index);
            glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride, attribute.pointer);
        }
    }
} // namespace gfx
