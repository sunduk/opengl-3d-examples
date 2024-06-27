#pragma once

#include <vector>
#include <list>

#include "glm/glm.hpp"

#include "Vertex.h"

class Hermite
{
public:
    Hermite();
    virtual ~Hermite();

    void Set(glm::vec3 begin, glm::vec3 tangentU, glm::vec3 end, glm::vec3 tangentV);
    glm::vec3 Evaluate(float t);
    static glm::vec3 Evaluate3(glm::vec3 begin, glm::vec3 tangentU, glm::vec3 end, glm::vec3 tangentV, float t);

private:
    glm::vec3 mBegin;
    glm::vec3 mEnd;

    glm::vec3 mTangentU;
    glm::vec3 mTangentV;
};
