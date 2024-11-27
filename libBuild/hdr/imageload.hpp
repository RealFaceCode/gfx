#pragma once

#include "defines.hpp"
#include <string>
#include "buffers/image.hpp"

namespace gfx
{
    Image LoadImageFromFile(const std::string& path, bool flip = false);
}