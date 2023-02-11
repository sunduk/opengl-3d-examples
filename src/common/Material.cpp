#pragma once

#include "Material.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::SetShader(Shader* shader)
{
    mShader = shader;
}

Shader* Material::GetShader() const
{
    return mShader;
}

void Material::SetPropertyVec3(const std::string& name, glm::vec3 value)
{
    mPropertiesVec3[name] = value;
}

const std::map<std::string, glm::vec3>& Material::GetPropertiesVec3() const
{
    return mPropertiesVec3;
}

void Material::AddTexture(unsigned int textureID)
{
    mTextureIDs.push_back(textureID);
}

const std::vector<unsigned int> Material::GetTextureIDs() const
{
    return mTextureIDs;
}