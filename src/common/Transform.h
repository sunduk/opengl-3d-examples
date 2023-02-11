#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Mesh.h"

class Transform
{
public:
    Transform();
    virtual ~Transform();

    void SetParent(Transform* parent);
    void AddChild(Transform* child);
    const glm::vec3& GetForward() const;
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;
    void SetQuaternion(const glm::quat& rotation);
    glm::quat GetQuaternion() const;
    glm::vec3 GetEulerAngles() const;
    void SetEulerAnglesOnLocalAxis(const glm::vec3& euler);
    void SetEulerAnglesOnWorldAxis(const glm::vec3& euler);
    void RotateOnLocalAxis(const glm::vec3& eulerAngles);
    void RotateOnWorldAxis(const glm::vec3& eulerAngles);
    void SetScale(const glm::vec3& scale);
    glm::vec3 GetScale() const;
    const glm::mat4& GetModelMatrix() const;

private:
    void RefreshMatrix();
    void RefreshAxis();

private:
    glm::vec3 mPosition{ 0,0,0 };
    glm::vec3 mEulerAngles{ 0,0,0 };
    glm::vec3 mScale{ 1,1,1 };
    glm::quat mRotation{ 1,0,0,0 };

    glm::vec3 mForward{ 0,0,1 };
    glm::vec3 mRight{ 1,0,0 };
    glm::vec3 mUp{ 0,1,0 };

    glm::mat4 mModelMatrix{1};

    Transform* mParent{};
    std::vector<Transform*> mChildren{};
};