#pragma once

#include "defines.hpp"
#include <glm/glm.hpp>

namespace gfx
{
    class GFX_API ClipSpace
    {
    public:
        ClipSpace() = default;
        ClipSpace(glm::vec2 pos, glm::vec2 size);
        ~ClipSpace() = default;

        void begin() const;
        void end() const;

    private:
        glm::vec2 pos;
        glm::vec2 size;
    };

    class GFX_API ScopedClipSpace
    {
    public:
        ScopedClipSpace() = delete;
        ScopedClipSpace(const ClipSpace& clipSpace);
        ~ScopedClipSpace();

    private:
        const ClipSpace& cs;
    };

    class GFX_API ScopedClipSpace2
    {
    public:
        ScopedClipSpace2() = delete;
        ScopedClipSpace2(glm::vec2 pos, glm::vec2 size);
        ~ScopedClipSpace2();

    private:
        glm::vec2 pos;
        glm::vec2 size;
    };
}