#pragma once

#include "GameObject.h"

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Line.h"
#include "Mesh.h"
#include "Material.h"
#include "SimpleMesh.h"

GameObject::GameObject()
{
}

GameObject::GameObject(unsigned int instanceId) :
    mInstanceId(instanceId)
{
}

GameObject::~GameObject()
{
}

void GameObject::SetMesh(Mesh* mesh)
{
    mMesh = mesh;
}

void GameObject::SetLine(Line* line)
{
    mLine = line;
}

void GameObject::SetMaterial(Material* material)
{
    mMaterial = material;
}

unsigned int GameObject::GetInstanceId()
{
    return mInstanceId;
}

void GameObject::Update(const ShaderParam& shaderParam, float deltaSec)
{
    SetMaterialProperties(mMaterial->GetShader(), shaderParam);
    DrawMesh();

    if (mMaterial->GetShader2() != nullptr)
    {
        SetMaterialProperties(mMaterial->GetShader2(), shaderParam);
        DrawMesh();
    }
}

void GameObject::SetMaterialProperties(Shader* shader, const ShaderParam& shaderParam)
{
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const glm::mat4 modelMatrix = mTransform.GetModelMatrix();
    glm::mat4 mvp = shaderParam.viewProjectionMatrix * modelMatrix;

    shader->Use();
    shader->SetMat4("mvp", mvp);

    glm::mat4 inverseModelMatrix = glm::inverse(modelMatrix);
    glm::mat3 normalMatrix = glm::transpose(inverseModelMatrix);
    shader->SetMat3("normalMatrix", normalMatrix);

    shader->SetVec3("lightDirection", shaderParam.lightDir);
    shader->SetVec3("lightColor", glm::clamp(shaderParam.lightColor, glm::vec3(0,0,0), glm::vec3(1,1,1)));
    shader->SetFloat("ambientIntensity", 0.2f);
    shader->SetVec3("cameraWorldPosition", shaderParam.cameraWorldPosition);
    shader->SetMat3("modelMatrix", modelMatrix);

    const std::map<std::string, glm::vec3>& propertiesVec3 = mMaterial->GetPropertiesVec3();
    for (const auto& element : propertiesVec3)
    {
        std::string key = element.first;
        glm::vec3 value = element.second;
        shader->SetVec3(key, value);
    }

    const std::vector<unsigned int> textureIDs = mMaterial->GetTextureIDs();
    for (int i = 0; i < textureIDs.size(); ++i)
    {
        shader->SetTexture(textureIDs[i], i);
    }
}

void GameObject::DrawMesh()
{
    if (mMesh != nullptr)
    {
        mMesh->Render();
    }

    if (mLine != nullptr)
    {
        mLine->Render();
    }
}
