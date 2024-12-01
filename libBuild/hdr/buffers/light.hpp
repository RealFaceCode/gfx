#pragma once

#include <glm/glm.hpp>

namespace gfx
{
    struct Light
    {
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
    };

    struct DirectionalLight
    {
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
        glm::vec3 direction;
    };

    struct PointLight
    {
        glm::vec3 position;
        glm::vec3 color;
        float intensity;
        float constant;
        float linear;
        float quadratic;
    };

    struct SpotLight
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 direction;
        float intensity;
        float constant;
        float linear;
        float quadratic;
        float cutOff;
        float outerCutOff;
    };

}