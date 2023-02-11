#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class Camera
{
public:
    enum class MovementDirection
    {
        Forward,
        Backward,
        Left,
        Right
    };

    Camera();
    Camera(glm::vec3 position);
    virtual ~Camera();
    glm::mat4 GetViewMatrix();

    void SetPosition(glm::vec3 position);
    void SetMoveDirection(glm::vec3 inputDirection);
    void AddMovement(MovementDirection direction);
    void RemoveMovement(MovementDirection direction);
    void ResetMovement();
    void SetSpeed(float speed);

    void AddYaw(float xoffset);
    void AddPitch(float yoffset);
    void ResetRotation();

    void SetMouseWheelOffset(float yoffset);
    float GetZoom();
    void SetZoome(float fov);

    void Update(float deltaTime);

private:
    void UpdateCameraVectors();

private:
    glm::vec3 mPosition{ 0,0,0 };
    glm::vec3 mForward{ 0,0,-1 };
    glm::vec3 mUp{ 0,1,0 };
    glm::vec3 mRight{ 1,0,0 };
    const glm::vec3 mWorldUp{ 0,1,0 };

    glm::vec3 mCurrentMovementDirection{};
    glm::vec3 mVelocity{};

    float mYaw{ 0.0f };
    float mPitch{ 0.0f };

    float mMovementSpeed{ 10.0f };
    float mFov{ 60.0f };
};