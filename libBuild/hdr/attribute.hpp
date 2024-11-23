#pragma once

#include "defines.hpp"

namespace gfx
{

    struct VertexArrayAttribute
    {
    public:
        VertexArrayAttribute(unsigned int index, int size, unsigned int type, bool normalized, int stride, void *pointer)
            : index(index), size(size), type(type), normalized(normalized), stride(stride), pointer(pointer), indexVBO(-1), typeVBO(-1) {}
    
        VertexArrayAttribute(unsigned int index, int size, unsigned int type, bool normalized, int stride, void *pointer, unsigned int indexVBO, unsigned int typeVBO)
            : index(index), size(size), type(type), normalized(normalized), stride(stride), pointer(pointer), indexVBO(indexVBO), typeVBO(typeVBO) {}
        
        unsigned int index;
        int size;
        unsigned int type;
        bool normalized;
        int stride;
        void *pointer;
        unsigned int indexVBO;
        unsigned int typeVBO;
    };

} // namespace gfx