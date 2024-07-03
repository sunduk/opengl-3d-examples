#pragma once

#include <vector>
#include <list>

#include "glm/glm.hpp"

#include "Vertex.h"

class CatmullRomSpline
{
public:
    CatmullRomSpline();
    virtual ~CatmullRomSpline();

    void Add(glm::vec3 point);
    glm::vec3 Evaluate(float t);
    glm::vec3 Evaluate3(float t);
    void SetTension(float tension);

private:
    std::vector<glm::vec3> mPoints{};
    float mTension{ 0.5f };
};
