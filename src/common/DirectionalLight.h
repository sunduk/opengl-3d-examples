#pragma once

#include "glm/glm.hpp"

#include "Transform.h"

class DirectionalLight
{
public:
    DirectionalLight();
    virtual ~DirectionalLight();

    const glm::vec4 GetDirection() const;
    const glm::vec3 GetColor() const;
    Transform& GetTransform();

    void SetColor(glm::vec3 color);

private:
    Transform mTransform{};
    glm::vec3 mColor{};
};