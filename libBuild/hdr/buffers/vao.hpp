#pragma once

#include "defines.hpp"

namespace gfx {
    struct GFX_API VAO {
    public:
        VAO();
        ~VAO();

        void bind();

    private:
        unsigned int vao;
    };

} // namespace gfx