#pragma once

#include "CatmullRomSpline.h"

#include <vector>

#include "glm/glm.hpp"
#include "HermiteSpline.h"

CatmullRomSpline::CatmullRomSpline()
{
}

CatmullRomSpline::~CatmullRomSpline()
{
}

void CatmullRomSpline::Add(glm::vec3 point)
{
    mPoints.push_back(point);
}

void CatmullRomSpline::SetTension(float tension)
{
    mTension = tension;
}

glm::vec3 CatmullRomSpline::Evaluate(float t)
{
    return Evaluate3(t);
}

glm::vec3 CatmullRomSpline::Evaluate3(float t)
{
    if (mPoints.size() < 3)
    {
        return glm::vec3();
    }

    HermiteSpline hermiteSpline{};

    // begin.
    hermiteSpline.Add(mPoints[0], glm::vec3());
    float tension = 1.0f - mTension;

    // points.
    int prev = 0;
    int next = 2;
    for (int i = 1; i < mPoints.size() - 1; ++i)
    {
        glm::vec3 tangent = glm::vec3();
        if (mPoints.size() > next)
        {
            tangent = (mPoints[next] - mPoints[prev]) * tension;
        }

        hermiteSpline.Add(mPoints[i], tangent);

        prev = i;
        next = i + 2;
    }

    // end.
    hermiteSpline.Add(mPoints[mPoints.size() - 1], glm::vec3());

    return hermiteSpline.Evaluate(t);
}
