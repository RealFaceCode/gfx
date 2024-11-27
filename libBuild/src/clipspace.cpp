#include "clipspace.hpp"

#include <glad/glad.h>

namespace gfx
{
    ClipSpace::ClipSpace(glm::vec2 pos, glm::vec2 size)
    : pos(pos), size(size)
    {}

    void ClipSpace::begin() const
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(pos.x, pos.y, size.x, size.y);
    }

    void ClipSpace::end() const
    {
        glDisable(GL_SCISSOR_TEST);
    }

    ScopedClipSpace::ScopedClipSpace(const ClipSpace& clipSpace)
    : cs(clipSpace)
    {
        cs.begin();
    }

    ScopedClipSpace::~ScopedClipSpace()
    {
        cs.end();
    }

    ScopedClipSpace2::ScopedClipSpace2(glm::vec2 pos, glm::vec2 size)
    : pos(pos), size(size)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(pos.x, pos.y, size.x, size.y);
    }

    ScopedClipSpace2::~ScopedClipSpace2()
    {
        glDisable(GL_SCISSOR_TEST);
    }
}