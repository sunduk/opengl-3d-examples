#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Material.h"
#include "Shader.h"
#include "Vertex.h"

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();
    void Initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Render();
    void Draw(const ShaderParam& shaderParam, const Material& material, const glm::mat4& modelMatrix);

private:
    std::vector<Vertex> mVertices{};
    std::vector<unsigned int> mIndices{};

    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
    unsigned int mElementBufferObjectId{};
};