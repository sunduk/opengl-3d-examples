#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Material.h"
#include "Shader.h"
#include "Vertex.h"

class Line
{
public:
    Line();
    virtual ~Line();
    void Initialize(const std::vector<Vertex>& vertices);
    void Render();

private:
    std::vector<Vertex> mVertices{};

    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
};