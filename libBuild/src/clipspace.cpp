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

    const glm::vec2& ClipSpace::getPos() const
    {
        return pos;
    }

    const glm::vec2& ClipSpace::getSize() const
    {
        return size;
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

    const glm::vec2& ScopedClipSpace::getPos() const
    {
        return cs.getPos();
    }

    const glm::vec2& ScopedClipSpace::getSize() const
    {
        return cs.getSize();
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

    const glm::vec2& ScopedClipSpace2::getPos() const
    {
        return pos;
    }

    const glm::vec2& ScopedClipSpace2::getSize() const
    {
        return size;
    }
}