#pragma once

#include <string>
#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class ObjLoader
{
public:
	ObjLoader(const std::string& filePath);
	virtual ~ObjLoader();

public:
	std::vector<Vertex> mVertices{};
	std::vector<unsigned int> mIndices{};
};