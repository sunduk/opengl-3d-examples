#pragma once

#include "Hermite.h"

#include <vector>

#include "glm/glm.hpp"

Hermite::Hermite()
{
    mBegin = glm::vec3();
    mEnd = glm::vec3();
    mTangentU = glm::vec3();
    mTangentV = glm::vec3();
}

Hermite::~Hermite()
{
}

void Hermite::Set(glm::vec3 begin, glm::vec3 tangentU, glm::vec3 end, glm::vec3 tangentV)
{
    mBegin = begin;
    mTangentU = tangentU;

    mEnd = end;
    mTangentV = tangentV;
}

glm::vec3 Hermite::Evaluate(float t)
{
    return Evaluate3(mBegin, mTangentU, mEnd, mTangentV, t);
}

glm::vec3 Hermite::Evaluate3(glm::vec3 begin, glm::vec3 tangentU, glm::vec3 end, glm::vec3 tangentV, float t)
{
    glm::vec3 a = begin;
    glm::vec3 b = begin + tangentU;
    glm::vec3 c = end - tangentV;
    glm::vec3 d = end;

    glm::vec3 ab = a + (b - a) * t;
    glm::vec3 bc = b + (c - b) * t;
    glm::vec3 cd = c + (d - c) * t;

    glm::vec3 abc = ab + (bc - ab) * t;
    glm::vec3 bcd = bc + (cd - bc) * t;
    return abc + (bcd - abc) * t;
}
