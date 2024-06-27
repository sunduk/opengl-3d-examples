#pragma once

#include <vector>
#include <list>

#include "glm/glm.hpp"

#include "Hermite.h"
#include "Vertex.h"

class HermiteSpline
{
public:
    HermiteSpline();
    virtual ~HermiteSpline();

    void Add(glm::vec3 position, glm::vec3 tangent);
    glm::vec3 Evaluate(float t);

private:
    std::vector<glm::vec3> mPositions;
    std::vector<glm::vec3> mTangents;
};
