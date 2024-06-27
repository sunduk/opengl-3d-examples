#pragma once

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	mTransform.RotateOnWorldAxis(glm::vec3(-90.0f, 0.0f, -45.0f));
	mColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

DirectionalLight::~DirectionalLight()
{
}

const glm::vec4 DirectionalLight::GetDirection() const
{
	return glm::vec4(mTransform.GetForward(), 0.0f);
}

const glm::vec3 DirectionalLight::GetColor() const
{
	return mColor;
}

Transform& DirectionalLight::GetTransform()
{
	return mTransform;
}

void DirectionalLight::SetColor(glm::vec3 color)
{
	mColor = color;
}