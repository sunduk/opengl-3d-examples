#include "SimpleTransform.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

SimpleTransform::SimpleTransform()
{
}

SimpleTransform::~SimpleTransform()
{
}

void SimpleTransform::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    RefreshMatrix();
}

glm::vec3 SimpleTransform::GetPosition() const
{
    return mPosition;
}

void SimpleTransform::SetEulerAngles(const glm::vec3& eulerAngles)
{
    mEulerAngles = glm::radians(eulerAngles);
    RefreshMatrix();
}

glm::vec3 SimpleTransform::GetEulerAngles() const
{
    return glm::degrees(mEulerAngles);
}

void SimpleTransform::SetScale(const glm::vec3& scale)
{
    mScale = scale;
    RefreshMatrix();
}

glm::vec3 SimpleTransform::GetScale() const
{
    return mScale;
}

const glm::mat4& SimpleTransform::GetModelMatrix() const
{
    return mModelMatrix;
}

void SimpleTransform::RefreshMatrix()
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition);

    glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1), mEulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1), mEulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1), mEulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationMatrixY * rotationMatrixX * rotationMatrixZ;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale);

    mModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}