#include "buffers/ubo.hpp"
#include <glad/glad.h>
#include "gfx.hpp"

namespace gfx
{
    static eutil::idp::IDPool idPool(0, GetMaxUBOSiumultaneousBindings());

    UBO::UBO()
    : buffer(0), id(), size(0)
    {}

    UBO::UBO(uint64_t size, int mode)
    : size(size)
    {
        create(size, nullptr, mode);
    }

    UBO::UBO(uint64_t size, void* data, int mode)
    {
        create(size, data, mode);
    }

    UBO::~UBO()
    {
        glDeleteBuffers(1, &buffer);
    }

    void UBO::map(uint64_t offset, int flag, void* data)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, id.get(), buffer);
        uint8_t* map = (uint8_t*)glMapBufferRange(GL_UNIFORM_BUFFER, offset, size, flag);
        memcpy(map, data, size);
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }

    void UBO::map(uint64_t offset, uint64_t size, int flag, void* data)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, id.get(), buffer);
        uint8_t* map = (uint8_t*)glMapBufferRange(GL_UNIFORM_BUFFER, offset, size, flag);
        memcpy(map, data, size);
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }

    void UBO::create(uint64_t size, void* data, int mode)
    {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
        id = idPool.getID();
    }

    uint32_t UBO::getID() const
    {
        return buffer;
    }

    uint64_t UBO::getBlockID() const
    {
        return id.get();
    }
}