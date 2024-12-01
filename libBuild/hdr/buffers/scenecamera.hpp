#pragma once

#include <string>
#include <glm/glm.hpp>

namespace gfx
{
    struct SceneCamera
    {
        glm::vec3 position;
        glm::vec3 lookAt;
        glm::vec3 up;
        float aspect;
        float near;
        float far;
        float fov;
        float orthoWidth;
        std::string name;
    };
}