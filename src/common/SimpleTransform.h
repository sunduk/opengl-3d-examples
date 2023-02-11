#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

class SimpleTransform
{
public:
    SimpleTransform();
    virtual ~SimpleTransform();

    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;

    void SetEulerAngles(const glm::vec3& eulerAngles);
    glm::vec3 GetEulerAngles() const;

    void SetScale(const glm::vec3& scale);
    glm::vec3 GetScale() const;

    const glm::mat4& GetModelMatrix() const;

private:
    void RefreshMatrix();

private:
    glm::vec3 mPosition{ 0,0,0 };
    glm::vec3 mEulerAngles{ 0,0,0 };
    glm::vec3 mScale{ 1,1,1 };

    glm::mat4 mModelMatrix{1};
};