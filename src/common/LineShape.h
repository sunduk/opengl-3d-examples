#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class LineShape
{
public:
    explicit LineShape(glm::vec3 begin);
    virtual ~LineShape();
    void AddPosition(glm::vec3 end);

private:
    void AddQuad(glm::vec3 end);

public:
    std::vector<Vertex> mVertices{};
    std::vector<unsigned int> mIndices{};

private:
    glm::vec3 mBegin;
    unsigned int mLastIndexV1;
    unsigned int mLastIndexV3;
    std::vector<glm::vec3> mBegins;
};
