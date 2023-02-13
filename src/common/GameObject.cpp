#pragma once

#include "GameObject.h"

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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

void GameObject::SetSimpleMesh(SimpleMesh* mesh)
{
    mSimpleMesh = mesh;
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
    SetMaterialProperties(shaderParam);
    DrawMesh();
}

void GameObject::SetMaterialProperties(const ShaderParam& shaderParam)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const glm::mat4 modelMatrix = mTransform.GetModelMatrix();
    glm::mat4 mvp = shaderParam.viewProjectionMatrix * modelMatrix;

    mMaterial->GetShader()->Use();
    mMaterial->GetShader()->SetMat4("mvp", mvp);

    glm::mat4 inverseModelMatrix = glm::inverse(modelMatrix);
    glm::mat3 normalMatrix = glm::transpose(inverseModelMatrix);
    mMaterial->GetShader()->SetMat3("normalMatrix", normalMatrix);

    mMaterial->GetShader()->SetVec3("lightDirection", shaderParam.lightDir);
    mMaterial->GetShader()->SetVec3("lightColor", shaderParam.lightColor);
    mMaterial->GetShader()->SetFloat("ambientIntensity", 0.2f);

    const std::map<std::string, glm::vec3>& propertiesVec3 = mMaterial->GetPropertiesVec3();
    for (const auto& element : propertiesVec3)
    {
        std::string key = element.first;
        glm::vec3 value = element.second;
        mMaterial->GetShader()->SetVec3(key, value);
    }

    const std::vector<unsigned int> textureIDs = mMaterial->GetTextureIDs();
    for (int i = 0; i < textureIDs.size(); ++i)
    {
        mMaterial->GetShader()->SetTexture(textureIDs[i], i);
    }
}

void GameObject::DrawMesh()
{
    mMesh->Render();
}

void GameObject::DrawSimpleMesh()
{
    mSimpleMesh->Render();
}