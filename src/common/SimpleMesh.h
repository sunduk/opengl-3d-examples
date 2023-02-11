#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class SimpleMesh
{
public:
    SimpleMesh();
    virtual ~SimpleMesh();
    void Initialize(const std::vector<VertexUV>& vertices, const std::vector<unsigned int>& indices);
    void Initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Render();
    void RefreshVertexBuffer();

public:
    std::vector<VertexUV> mVertices{};
    std::vector<Vertex> mVerticesEx{};
    std::vector<unsigned int> mIndices{};
    unsigned int mIndexSize{};

    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
    unsigned int mElementBufferObjectId{};
};