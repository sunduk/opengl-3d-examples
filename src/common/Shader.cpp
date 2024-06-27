#pragma once

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

Shader::Shader()
{
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    Load(vertexPath, fragmentPath);
}

bool Shader::Load(std::string vertexPath, std::string fragmentPath)
{
    auto LoadTextFile = [](const std::string& filePath)
    {
        std::ifstream shaderFile(filePath);
        std::stringstream stream{};
        stream << shaderFile.rdbuf();
        std::string text = stream.str();
        shaderFile.close();
        return text;
    };

    std::string vertexCode{};
    std::string fragmentCode{};

    try
    {
        vertexCode = LoadTextFile(vertexPath);
        fragmentCode = LoadTextFile(fragmentPath);
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "[error] shader file read error : " << e.what() << std::endl;
        return false;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // compile shaders
    unsigned int vertex{};
    unsigned int fragment{};

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckShaderCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckShaderCompileErrors(fragment, "FRAGMENT");

    // shader Program
    mID = glCreateProgram();
    glAttachShader(mID, vertex);
    glAttachShader(mID, fragment);

    glLinkProgram(mID);
    CheckShaderCompileErrors(mID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

Shader::~Shader()
{
}

void Shader::SetDepthTestEnabled(bool isEnable)
{
    mIsDepthTest = isEnable;
}

void Shader::SetCullingEnabled(bool isEnable)
{
    mIsFaceCulling = isEnable;
}

void Shader::SetBackfaceCulling(bool isEnable)
{
    mIsBackfaceCulling = isEnable;
}

void Shader::SetFrontCCW(bool isEnable)
{
    mIsCCW = isEnable;
}

void Shader::Use()
{
    mIsDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    mIsFaceCulling ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    mIsBackfaceCulling ? glCullFace(GL_BACK) : glCullFace(GL_FRONT);
    mIsCCW ? glFrontFace(GL_CCW) : glFrontFace(GL_CW);

    glUseProgram(mID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::SetUInt(const std::string& name, unsigned int value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(mID, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetTexture(unsigned int textureID, unsigned int location) const
{
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(GL_TEXTURE_2D, textureID);
    std::string name = "sample" + std::to_string(location);
    glUniform1i(glGetUniformLocation(mID, name.c_str()), location);
}

void Shader::CheckShaderCompileErrors(unsigned int shader, std::string type)
{
    GLint success{};
    GLchar errorLog[1024]{};
    if ("PROGRAM" == type)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, errorLog);
            std::cout << "[error] shader program linking error. type" << type << std::endl;
            std::cout << "log : " << errorLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, errorLog);
            std::cout << "[error] shader compilation error. type" << type << std::endl;
            std::cout << "log : " << errorLog << std::endl;
        }
    }
}