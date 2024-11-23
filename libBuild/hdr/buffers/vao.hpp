#pragma once

#include "defines.hpp"
#include "attribute.hpp"
#include <vector>

namespace gfx {

    struct GFX_API VAO {
    public:
        VAO();
        ~VAO();

        void bind();
        void addAttribute(int size, unsigned int type, bool normalized, int stride, void* pointer);
        void addAttribute(int size, unsigned int type, bool normalized, int stride, void* pointer, unsigned int indexVBO, unsigned int typeVBO);
        void build();

    private:
        unsigned int vao;
        std::vector<VertexArrayAttribute> attributes;
    };

} // namespace gfx