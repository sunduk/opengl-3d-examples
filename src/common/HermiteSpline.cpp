#pragma once

#include "HermiteSpline.h"

#include <vector>

#include "glm/glm.hpp"

HermiteSpline::HermiteSpline()
{
}

HermiteSpline::~HermiteSpline()
{
}

void HermiteSpline::Add(glm::vec3 position, glm::vec3 tangent)
{
	mPositions.push_back(position);
	mTangents.push_back(tangent);
}

glm::vec3 HermiteSpline::Evaluate(float t)
{
	if (mPositions.size() < 2)
	{
		return glm::vec3();
	}

	float splineT = (mPositions.size() - 1) * t;
	int curveIndex = static_cast<int>(splineT);
	if (curveIndex >= mPositions.size() - 1)
	{
		return mPositions[mPositions.size() - 1];
	}

	// -- debugging --
	// t = 0
	// mPositions.size = 2 [0,1]
	// splineT = 0
	// curveIndex = 0
	// 0, 1

	// t = 0.5
	// mPositions.size = 3 [0,1,2]
	// splineT = 1
	// curveIndex = 1
	// 1, 2

	// t = 1
	// mPositions.size = 3 [0,1,2]
	// splineT = 2
	// curveIndex = 2
	// 2

	float curveT = splineT - curveIndex;
	glm::vec3 begin = mPositions[curveIndex];
	glm::vec3 end = mPositions[curveIndex + 1];
	glm::vec3 tangentU = mTangents[curveIndex];
	glm::vec3 tangentV = mTangents[curveIndex + 1];
	return Hermite::Evaluate3(begin, tangentU, end, tangentV, curveT);
}
