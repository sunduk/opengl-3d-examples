#pragma once

#include "Mesh.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}

void Mesh::Initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    mVertices = vertices;
    mIndices = indices;

    glGenVertexArrays(1, &mVertexArrayObjectId);
    glGenBuffers(1, &mVertexBufferObjectId);
    glGenBuffers(1, &mElementBufferObjectId);

    glBindVertexArray(mVertexArrayObjectId);
    {
        // copy to video memory.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObjectId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // attributes.
        // position.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // color.
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mColor));

        // normal.
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));

        // uv.
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));
    }
    glBindVertexArray(0);
}

void Mesh::Render()
{
    glBindVertexArray(mVertexArrayObjectId);
    {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
}

void Mesh::Draw(const ShaderParam& shaderParam, const Material& material, const glm::mat4& modelMatrix)
{
    material.GetShader()->Use();
    material.GetShader()->SetMat4("viewProjection", shaderParam.viewProjectionMatrix);
    material.GetShader()->SetMat4("model", modelMatrix);

    //TODO:shader로 빼서 한번만 처리 가능.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 inverseModelMatrix = glm::inverse(modelMatrix);
    glm::mat3 normalMatrix = glm::transpose(inverseModelMatrix);
    material.GetShader()->SetMat3("normalMatrix", normalMatrix);
    //TODO:로컬, 월드 좌표계 기준 체크.
    //material.GetShader()->SetVec3("lightDirection", glm::vec3(-1, -1, 0));
    material.GetShader()->SetVec3("lightDirection", shaderParam.lightDir);
    material.GetShader()->SetVec3("lightColor", shaderParam.lightColor);
    material.GetShader()->SetFloat("ambientIntensity", 0.2f);

    /*glm::mat4 inverseModelMatrix = glm::inverse(modelMatrix);
    glm::mat3 normalMatrix = glm::transpose(inverseModelMatrix);
    material.GetShader()->SetMat3("normalMatrix", normalMatrix);

    glm::vec3 localLightDir = inverseModelMatrix * shaderParam.lightDir;
    material.GetShader()->SetVec3("lightDir", localLightDir);*/

    const std::map<std::string, glm::vec3>& propertiesVec3 = material.GetPropertiesVec3();
    for (const auto& element : propertiesVec3)
    {
        material.GetShader()->SetVec3(element.first, element.second);
    }

    const std::vector<unsigned int> textureIDs = material.GetTextureIDs();
    for (int i = 0; i < textureIDs.size(); ++i)
    {
        material.GetShader()->SetTexture(textureIDs[i], i);
    }

    glBindVertexArray(mVertexArrayObjectId);
    {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
}