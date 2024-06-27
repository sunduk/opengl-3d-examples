#pragma once

#include <vector>
#include <list>

#include "glm/glm.hpp"

#include "Bezier.h"
#include "Vertex.h"

class BezierSpline
{
public:
    BezierSpline();
    virtual ~BezierSpline();

    void Add(glm::vec3 position);
    glm::vec3 Evaluate(float t);

private:
    std::vector<Bezier*> mCurves;
    std::vector<glm::vec3> mPositions;
};
