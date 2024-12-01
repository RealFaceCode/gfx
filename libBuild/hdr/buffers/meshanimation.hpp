#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace gfx
{
    struct MeshAnimation
    {
        std::string name;
        double duration;
        double ticksPerSecond;
        std::vector<std::pair<std::string, std::vector<glm::mat4>>> channels;
    };
}