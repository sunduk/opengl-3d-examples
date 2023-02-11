#pragma once

#include <string>

#include "glm/glm.hpp"

class Shader
{
public:
    Shader();
    Shader(std::string vertexPath, std::string fragmentPath);
    virtual ~Shader();
    bool Load(std::string vertexPath, std::string fragmentPath);
    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetUInt(const std::string& name, unsigned int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w);
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    void SetTexture(unsigned int textureID, unsigned int location) const;

private:
    void CheckShaderCompileErrors(unsigned int shader, std::string type);

private:
    unsigned int mID{};
};

struct ShaderParam
{
    glm::mat4 projectionMatrix{};
    glm::mat4 viewMatrix{};
    glm::mat4 viewProjectionMatrix{};
    glm::vec4 lightDir{};
    glm::vec3 lightColor{};
};