#pragma once

#include "BezierSpline.h"

#include <vector>

#include "glm/glm.hpp"

BezierSpline::BezierSpline()
{
}

BezierSpline::~BezierSpline()
{
	for (int i = 0; i < mCurves.size(); ++i)
	{
		delete mCurves[i];
	}

	mCurves.clear();
}

void BezierSpline::Add(glm::vec3 position)
{
	mPositions.push_back(position);

	if (mPositions.size() == 4)
	{
		Bezier* curve = new Bezier();
		curve->Add(mPositions[0], mPositions[1], mPositions[2], mPositions[3]);

		mCurves.push_back(curve);
		mPositions.clear();
	}
}

glm::vec3 BezierSpline::Evaluate(float t)
{
	if (mCurves.empty())
	{
		return glm::vec3();
	}

	float splineT = mCurves.size() * t;
	int curveIndex = static_cast<int>(splineT);
	if (curveIndex >= mCurves.size())
	{
		return mCurves[mCurves.size() - 1]->Evaluate(1);
	}

	float curveT = splineT - curveIndex;
	return mCurves[curveIndex]->Evaluate(curveT);

}
