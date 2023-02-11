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
    DrawMesh(shaderParam);
}

void GameObject::DrawMesh(const ShaderParam& shaderParam)
{
    const glm::mat4 modelMatrix = mTransform.GetModelMatrix();
    mMesh->Draw(shaderParam, *mMaterial, modelMatrix);
}

void GameObject::DrawMesh()
{
    mMesh->Render();
}

void GameObject::DrawSimpleMesh()
{
    mSimpleMesh->Render();
}