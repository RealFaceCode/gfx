#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace gfx {
    Camera::Camera(CameraType type, glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch, float aspect)
        : type(type), position(startPosition), worldUp(upDirection), updateView(true), updateProjection(true), yaw(startYaw),
        pitch(startPitch), movementSpeed(2.5f), mouseSensitivity(0.1f), fov(45.0f), near(0.1f), far(100.0f),
        aspect(aspect), maxFov(45.0f), minFov(1.0f), maxPitch(89.0f), minPitch(-89.0f)
    {
        updateCameraVectors();
        update();
    }

    Camera::Camera(CameraType type, glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch, float movementSpeed, float mouseSensitivity, float fov, float near, float far, float aspect, float maxFov, float minFov, float maxPitch, float minPitch)
        : type(type), position(startPosition), worldUp(upDirection), updateView(true), updateProjection(true), yaw(startYaw),
        pitch(startPitch), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity), fov(fov), near(near),
        far(far), aspect(aspect), maxFov(maxFov), minFov(minFov), maxPitch(maxPitch), minPitch(minPitch)
    {
        updateCameraVectors();
        update();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return view;
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return projection;
    }

    void Camera::processMovement(CameraMovement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        switch(direction)
        {
            case CameraMovement::FORWARD:
                position += front * velocity;
                break;
            case CameraMovement::BACKWARD:
                position -= front * velocity;
                break;
            case CameraMovement::LEFT:
                position -= right * velocity;
                break;
            case CameraMovement::RIGHT:
                position += right * velocity;
                break;
            case CameraMovement::UP:
                position += up * velocity;
                break;
            case CameraMovement::DOWN:
                position -= up * velocity;
                break;
        }
        updateView = true;
    }

    void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (constrainPitch)
        {
            if(pitch > maxPitch)
                pitch = maxPitch;
            if(pitch < minPitch)
                pitch = minPitch;
        }

        updateCameraVectors();
    }

    void Camera::processMouseScroll(float yoffset)
    {
        fov -= yoffset;
        if(fov > maxFov)
            fov = maxFov;
        if(fov < minFov)
            fov = minFov;

        updateProjection = true;
    }

    std::pair<bool, bool> Camera::update()
    {
        bool viewUpdated = updateView;
        bool projectionUpdated = updateProjection;

        if(updateView)
        {
            updateViewMatrix();
            updateView = false;
        }

        if(updateProjection)
        {
            updateProjectionMatrix();
            updateProjection = false;
        }

        return {viewUpdated, projectionUpdated};
    }

    void Camera::updateCameraVectors()
    {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
        updateView = true;
    }

    void Camera::updateViewMatrix()
    {
        view = glm::lookAt(position, position + front, up);
    }

    void Camera::updateProjectionMatrix()
    {
        switch (type)
        {
        case CameraType::PERSPECTIVE:
            projection = glm::perspective(glm::radians(fov), aspect, near, far);
            break;
        case CameraType::ORTHOGRAPHIC:
            projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near, far);
            break;
        default:
            break;
        }
    }

    void Camera::setPosition(glm::vec3 position)
    {
        this->position = position;
        updateView = true;
    }

    void Camera::setYaw(float yaw)
    {
        this->yaw = yaw;
        updateCameraVectors();
    }

    void Camera::setPitch(float pitch)
    {
        this->pitch = pitch;
        updateCameraVectors();
    }

    void Camera::setMovementSpeed(float movementSpeed)
    {
        this->movementSpeed = movementSpeed;
    }

    void Camera::setMouseSensitivity(float mouseSensitivity)
    {
        this->mouseSensitivity = mouseSensitivity;
    }

    void Camera::setFov(float fov)
    {
        this->fov = fov;
        updateProjection = true;
    }

    void Camera::setNear(float near)
    {
        this->near = near;
        updateProjection = true;
    }

    void Camera::setAspect(float aspect)
    {
        this->aspect = aspect;
        updateProjection = true;
    }

    void Camera::setFar(float far)
    {
        this->far = far;
        updateProjection = true;
    }

    void Camera::setMaxFov(float maxFov)
    {
        this->maxFov = maxFov;
    }

    void Camera::setMinFov(float minFov)
    {
        this->minFov = minFov;
    }

    void Camera::setMaxPitch(float maxPitch)
    {
        this->maxPitch = maxPitch;
    }

    void Camera::setMinPitch(float minPitch)
    {
        this->minPitch = minPitch;
    }
} // namespace gfx
