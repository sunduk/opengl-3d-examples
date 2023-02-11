#pragma once

#include "Camera.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 position)
{
    mPosition = position;
    UpdateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mForward, mUp);
}

void Camera::SetPosition(glm::vec3 position)
{
    mPosition = position;
}

void Camera::SetMoveDirection(glm::vec3 inputDirection)
{
    glm::vec3 moveDirection = (mForward * -inputDirection.z) + (mRight * inputDirection.x);
    mVelocity = moveDirection * mMovementSpeed;
}

void Camera::SetSpeed(float speed)
{
    mMovementSpeed = speed;
}

void Camera::AddMovement(MovementDirection direction)
{
    switch (direction)
    {
    case MovementDirection::Forward:
        mCurrentMovementDirection.z = -1.0f;
        break;

    case MovementDirection::Backward:
        mCurrentMovementDirection.z = 1.0f;
        break;

    case MovementDirection::Left:
        mCurrentMovementDirection.x = -1.0f;
        break;

    case MovementDirection::Right:
        mCurrentMovementDirection.x = 1.0f;
        break;
    }

    SetMoveDirection(mCurrentMovementDirection);
}

void Camera::RemoveMovement(MovementDirection direction)
{
    switch (direction)
    {
    case MovementDirection::Forward:
    case MovementDirection::Backward:
        mCurrentMovementDirection.z = 0.0f;
        break;

    case MovementDirection::Left:
    case MovementDirection::Right:
        mCurrentMovementDirection.x = 0.0f;
        break;
    }

    SetMoveDirection(mCurrentMovementDirection);
}

void Camera::ResetMovement()
{
    mCurrentMovementDirection = glm::vec3(0);
    SetMoveDirection(mCurrentMovementDirection);
}

void Camera::AddYaw(float xoffset)
{
    mYaw += xoffset;
    std::cout << mYaw << std::endl;
}

void Camera::AddPitch(float yoffset)
{
    mPitch += yoffset;

    if (mPitch > 89.0f)
    {
        mPitch = 89.0f;
    }
    else if (mPitch < -89.0f)
    {
        mPitch = -89.0f;
    }
}

void Camera::ResetRotation()
{
    mYaw = 0.0f;
    mPitch = 0.0f;
}

void Camera::Update(float deltaTime)
{
    mPosition += mVelocity * deltaTime;

    UpdateCameraVectors();
}

void Camera::SetMouseWheelOffset(float yoffset)
{
    mFov -= (float)yoffset;
    if (mFov < 1.0f)
    {
        mFov = 1.0f;
    }

    if (mFov > 90.0f)
    {
        mFov = 90.0f;
    }
}

float Camera::GetZoom()
{
    return mFov;
}

void Camera::SetZoome(float fov)
{
    mFov = fov;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front{};
    front.z = -cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.x = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mForward = glm::normalize(front);

    mRight = glm::normalize(glm::cross(mForward, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mForward));
}