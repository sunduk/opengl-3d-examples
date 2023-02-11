#include "Transform.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::SetParent(Transform* parent)
{
    mParent = parent;
    mParent->AddChild(this);
    RefreshMatrix();
}

void Transform::AddChild(Transform* child)
{
    mChildren.push_back(child);
    child->mParent = this;
    child->RefreshMatrix();
}

const glm::vec3& Transform::GetForward() const
{
    return mForward;
}

void Transform::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    RefreshMatrix();
}

glm::vec3 Transform::GetPosition() const
{
    return mPosition;
}

void Transform::SetQuaternion(const glm::quat& rotation)
{
    mRotation = rotation;
    mEulerAngles = glm::eulerAngles(mRotation);
    RefreshMatrix();
    RefreshAxis();
}

glm::quat Transform::GetQuaternion() const
{
    return mRotation;
}

glm::vec3 Transform::GetEulerAngles() const
{
    return glm::degrees(mEulerAngles);
}

void Transform::SetEulerAnglesOnLocalAxis(const glm::vec3& euler)
{
    glm::quat rotation = glm::quat(glm::radians(euler));
    SetQuaternion(rotation);

    //TODO:잘못된 방식. 원인 파악 후 정리 필요.
    //mEulerAngles = glm::radians(euler);
    //mRotation = glm::quat(mEulerAngles);
    //RefreshMatrix();
    //RefreshAxis();
}

void Transform::SetEulerAnglesOnWorldAxis(const glm::vec3& euler)
{
    glm::quat rotation = glm::quat(glm::radians(euler));
    SetQuaternion((glm::inverse(mRotation) * rotation * mRotation));

    //TODO:잘못된 방식. 원인 파악 후 정리 필요.
    /*mEulerAngles = glm::radians(euler);
    mRotation = glm::quat(glm::vec3(mEulerAngles.x, mEulerAngles.y, -mEulerAngles.z));
    mRotation.z *= -1.0f;
    RefreshMatrix();
    RefreshAxis();*/
}

void Transform::RotateOnLocalAxis(const glm::vec3& eulerAngles)
{
    glm::quat rotation = glm::quat(glm::radians(eulerAngles));
    SetQuaternion(mRotation * rotation);

    //TODO:잘못된 방식. 원인 파악 후 정리 필요.
    /*mEulerAngles += glm::radians(eulerAngles);
    mRotation = glm::quat(mEulerAngles);
    RefreshMatrix();
    RefreshAxis();*/
}

void Transform::RotateOnWorldAxis(const glm::vec3& eulerAngles)
{
    glm::quat rotation = glm::quat(glm::radians(eulerAngles));
    SetQuaternion(mRotation * (glm::inverse(mRotation) * rotation * mRotation));

    //TODO:잘못된 방식. 원인 파악 후 정리 필요.
    /*mEulerAngles += glm::radians(eulerAngles);
    mRotation = glm::quat(glm::vec3(mEulerAngles.x, mEulerAngles.y, -mEulerAngles.z));
    mRotation.z *= -1.0f;
    RefreshMatrix();
    RefreshAxis();*/
}

void Transform::SetScale(const glm::vec3& scale)
{
    mScale = scale;
    RefreshMatrix();
}

glm::vec3 Transform::GetScale() const
{
    return mScale;
}

const glm::mat4& Transform::GetModelMatrix() const
{
    return mModelMatrix;
}

void Transform::RefreshMatrix()
{
    if (mParent != nullptr)
    {
        glm::mat4 selfMatrix = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(mRotation) * glm::scale(glm::mat4(1.0f), mScale);
        mModelMatrix = mParent->GetModelMatrix() * selfMatrix;
    }
    else
    {
        mModelMatrix = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(mRotation) * glm::scale(glm::mat4(1.0f), mScale);
    }

    RefreshAxis();

    for (int i = 0; i < mChildren.size(); ++i)
    {
        mChildren[i]->RefreshMatrix();
    }
}

void Transform::RefreshAxis()
{
    mForward = mRotation * glm::vec3(0.0f, 0.0f, -1.0f);
    mUp = mRotation * glm::vec3(0, 1, 0);
    mRight = glm::cross(mForward, mUp);
}