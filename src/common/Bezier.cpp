#pragma once

#include "Bezier.h"

#include <vector>

#include "glm/glm.hpp"

Bezier::Bezier()
{
}

Bezier::~Bezier()
{
}

void Bezier::Add(glm::vec3 begin, glm::vec3 controlPoint0, glm::vec3 controlPoint1, glm::vec3 end)
{
	mPoints.clear();
	mPoints.push_back(begin);
	mPoints.push_back(controlPoint0);
	mPoints.push_back(controlPoint1);
	mPoints.push_back(end);
}

glm::vec3 Bezier::Evaluate(float t)
{
	if (mPoints.size() == 3)
	{
		return Evaluate2(t);
	}
	else if (mPoints.size() == 4)
	{
		return Evaluate3(t);
	}

	return glm::vec3();
}

glm::vec3 Bezier::Evaluate2(float t)
{
	glm::vec3 a = mPoints[0];
	glm::vec3 b = mPoints[1];
	glm::vec3 c = mPoints[2];

	glm::vec3 ab = a + (b - a) * t;
	glm::vec3 bc = b + (c - b) * t;

	return ab + (bc - ab) * t;
}

glm::vec3 Bezier::Evaluate3(float t)
{
    glm::vec3 a = mPoints[0];
    glm::vec3 b = mPoints[1];
    glm::vec3 c = mPoints[2];
    glm::vec3 d = mPoints[3];

    glm::vec3 ab = a + (b - a) * t;
    glm::vec3 bc = b + (c - b) * t;
    glm::vec3 cd = c + (d - c) * t;

    glm::vec3 abc = ab + (bc - ab) * t;
    glm::vec3 bcd = bc + (cd - bc) * t;
    return abc + (bcd - abc) * t;
}
