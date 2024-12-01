#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace gfx
{
    struct MeshAnimation
    {
        std::string name;
        float duration;
        float ticksPerSecond;
        std::vector<std::pair<std::string, std::vector<glm::mat4>>> channels;
    };
}