#include "ObjLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

ObjLoader::ObjLoader(const std::string& filePath)
{
	std::vector<unsigned int> vertexIndices{};
	std::vector<unsigned int> uvIndices{};
	std::vector<unsigned int> normalIndices{};
	std::vector<glm::vec3> vertices{};
	std::vector<glm::vec2> uvs{};
	std::vector<glm::vec3> normals{};

	std::ifstream file(filePath);
	std::string line{};
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string prefix{};
		stream >> prefix;

		if (prefix == "v")
		{
			glm::vec3 vertex{};
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (prefix == "vt")
		{
			glm::vec2 uv{};
			stream >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (prefix == "vn")
		{
			glm::vec3 normal{};
			stream >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (prefix == "f")
		{
			unsigned int vertexIndex[3]{};
			unsigned int uvIndex[3]{};
			unsigned int normalIndex[3]{};
			char slash{};
			stream >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0] >>
				vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1] >>
				vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); ++i)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		Vertex v{};
		v.mPosition = vertices[vertexIndex - 1];
		v.mNormal = normals[normalIndex - 1];
		v.mUV = uvs[uvIndex - 1];

		mVertices.push_back(v);
		mIndices.push_back(i);
	}
}

ObjLoader::~ObjLoader()
{
}