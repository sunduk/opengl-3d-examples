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

private:
    std::vector<Vertex> mVertices{};
    std::vector<unsigned int> mIndices{};

    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
    unsigned int mElementBufferObjectId{};
};