#pragma once

#include "defines.hpp"
#include <cstdint>
#include "idp.hpp"

namespace gfx
{
    class GFX_API UBO
    {
    public:
        UBO();
        UBO(uint64_t size, int mode);
        UBO(uint64_t size, void* data, int mode);
        ~UBO();

        void map(uint64_t offset, int flag, void* data);
        void map(uint64_t offset, uint64_t size ,int flag, void* data);

        uint32_t getID() const;
        uint64_t getBlockID() const;

    private:
        void create(uint64_t size, void* data, int mode);
        uint32_t buffer;
        eutil::idp::ID id;
        uint64_t size;
    };
}