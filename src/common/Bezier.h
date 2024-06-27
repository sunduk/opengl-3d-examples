#pragma once

#include <vector>
#include <list>

#include "glm/glm.hpp"

#include "Vertex.h"

class Bezier
{
public:
    Bezier();
    virtual ~Bezier();

    void Add(glm::vec3 begin, glm::vec3 controlPoint0, glm::vec3 controlPoint1, glm::vec3 end);
    glm::vec3 Evaluate(float t);
    glm::vec3 Evaluate2(float t);
    glm::vec3 Evaluate3(float t);

private:
    std::vector<glm::vec3> mPoints;
};
