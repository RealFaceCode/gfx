#pragma once

#include "defines.hpp"

namespace gfx
{

    struct VertexBufferAttribute
    {
    public:
        VertexBufferAttribute(unsigned int index, int size, unsigned int type, bool normalized, int stride, void *pointer)
            : index(index), size(size), type(type), normalized(normalized), stride(stride), pointer(pointer) {}

        unsigned int index;
        int size;
        unsigned int type;
        bool normalized;
        int stride;
        void *pointer;
    };

} // namespace gfx