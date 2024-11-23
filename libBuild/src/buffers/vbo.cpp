#include "buffers/vbo.hpp"

#include <glad/glad.h>
#include <lc.hpp>

namespace gfx
{
    
    VBO::VBO()
    {
        glGenBuffers(1, &vbo);
        bind();
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &vbo);
    }

    void VBO::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }

    void VBO::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::setData(unsigned int size, void* data, unsigned int usage)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    void VBO::setSubData(unsigned int offset, unsigned int size, void* data)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void VBO::addLayout(int size, unsigned int type, bool normalized, int stride, void* pointer)
    {
        attributes.emplace_back(VertexBufferAttribute(attributes.size(), size, type, normalized, stride, pointer));
    }

    void VBO::addLayout(int location, int size, unsigned int type, bool normalized, int stride, void* pointer)
    {
        attributes.emplace_back(VertexBufferAttribute(location, size, type, normalized, stride, pointer));
    }

    void VBO::setLayout()
    {
        for(auto& attribute : attributes)
        {
            glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride, attribute.pointer);
            glEnableVertexAttribArray(attribute.index);
        }
    }
}