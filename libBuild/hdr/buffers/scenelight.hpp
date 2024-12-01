#pragma once

#include <string>
#include <glm/glm.hpp>

namespace gfx
{
    enum class SceneLightType
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    struct SceneLight
    {
        std::string name;
        SceneLightType type;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;
        float attenuationConstant;
        float attenuationLinear;
        float attenuationQuadratic;
        glm::vec3 colorDiffuse;
        glm::vec3 colorSpecular;
        glm::vec3 colorAmbient;
        float angleInnerCone;
        float angleOuterCone;
        glm::vec2 size;
    };
}