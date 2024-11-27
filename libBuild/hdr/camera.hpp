#pragma once

#include "defines.hpp"
#include <glm/glm.hpp>

namespace gfx {
    enum class CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum class CameraType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };

    class GFX_API Camera {
    public:
        Camera(CameraType type, glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch, float aspect);
        Camera(CameraType type, glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch, float movementSpeed, float mouseSensitivity, float fov, float near, float far, float aspect, float maxFov, float minFov, float maxPitch, float minPitch);

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
        void processMovement(CameraMovement direction, float deltaTime);
        void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void processMouseScroll(float yoffset);
        std::pair<bool, bool> update();

        void setPosition(glm::vec3 position);
        void setYaw(float yaw);
        void setPitch(float pitch);
        void setMovementSpeed(float movementSpeed);
        void setMouseSensitivity(float mouseSensitivity);
        void setFov(float fov);
        void setNear(float near);
        void setAspect(float aspect);
        void setFar(float far);
        void setMaxFov(float maxFov);
        void setMinFov(float minFov);
        void setMaxPitch(float maxPitch);
        void setMinPitch(float minPitch);
        void invertYAxisMouse(bool invert);

    private:
        void updateCameraVectors();
        void updateViewMatrix();
        void updateProjectionMatrix();

        CameraType type;
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        glm::mat4 view;
        glm::mat4 projection;
        bool updateView;
        bool updateProjection;
        bool invertYAixsMouse;

        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float fov;
        float near;
        float far;
        float aspect;
        float maxFov;
        float minFov;
        float maxPitch;
        float minPitch;
    };
} // namespace gfx