#pragma once

#include "defines.hpp"
#include "attribute.hpp"
#include <vector>

namespace gfx {

    struct GFX_API VBO {
    public:
        VBO();
        ~VBO();

        void bind();
        void unbind();
        void setData(unsigned int size, void* data, unsigned int usage);
        void setSubData(unsigned int offset, unsigned int size, void* data);

        void addLayout(int size, unsigned int type, bool normalized, int stride, void* pointer);
        void addLayout(int location ,int size, unsigned int type, bool normalized, int stride, void* pointer);
        void setLayout();

    private:
        unsigned int vbo;
        std::vector<VertexBufferAttribute> attributes;
    };

} // namespace gfx