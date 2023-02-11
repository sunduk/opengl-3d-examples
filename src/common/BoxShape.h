#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class BoxShape
{
public:
    explicit BoxShape(glm::vec3 halfExtends = glm::vec3(1, 1, 1))
    {
        GenerateVertices(halfExtends);
        GenerateIndices();
    }

    const std::vector<Vertex>& GetVertices()
    {
        return mVertices;
    }

    const std::vector<unsigned int>& GetIndices()
    {
        return mIndices;
    }

private:
    void AddVertex(const Vertex& vertex)
    {
        mVertices.push_back(vertex);
    }

    void AddIndex(unsigned int index0, unsigned int index1, unsigned int index2)
    {
        mIndices.push_back(index0);
        mIndices.push_back(index1);
        mIndices.push_back(index2);
    }

    void GenerateVertices(glm::vec3 halfExtends)
    {
        glm::vec2 uvLeftTop = glm::vec2(0.0f, 1.0f);
        glm::vec2 uvLeftBottom = glm::vec2(0.0f, 0.0f);
        glm::vec2 uvRightBottom = glm::vec2(1.0f, 0.0f);
        glm::vec2 uvRightTop = glm::vec2(1.0f, 1.0f);

        glm::vec3 RED{ 1,0,0 };
        glm::vec3 WHITE{ 1,1,1 };
        glm::vec3 normal{ 0,1,0 };

        // order : {position, vertex-color, normal, uv}
        mVertices.reserve(24);
        //Top
        AddVertex({ halfExtends * glm::vec3(-1, 1, -1), WHITE, normal, uvLeftTop }); //0
        AddVertex({ halfExtends * glm::vec3(1, 1, -1), WHITE, normal, uvRightTop }); //1
        AddVertex({ halfExtends * glm::vec3(-1, 1,  1), WHITE, normal, uvLeftBottom }); //2
        AddVertex({ halfExtends * glm::vec3(1, 1,  1), WHITE, normal, uvRightBottom }); //3

        //Bottom
        normal = { 0, -1, 0 };
        AddVertex({ halfExtends * glm::vec3(1, -1, -1), WHITE, normal, uvLeftTop }); //4
        AddVertex({ halfExtends * glm::vec3(-1, -1, -1), WHITE, normal, uvRightTop }); //5
        AddVertex({ halfExtends * glm::vec3(1, -1, 1), WHITE, normal, uvLeftBottom }); //6
        AddVertex({ halfExtends * glm::vec3(-1, -1, 1), WHITE, normal, uvRightBottom });  //7

        //Front
        normal = { 0, 0, 1 };
        AddVertex({ halfExtends * glm::vec3(-1,  1, 1), RED, normal, uvLeftTop }); //8
        AddVertex({ halfExtends * glm::vec3(1,  1, 1),  RED, normal, uvRightTop }); //9
        AddVertex({ halfExtends * glm::vec3(-1, -1, 1), RED, normal, uvLeftBottom }); //10
        AddVertex({ halfExtends * glm::vec3(1, -1, 1),  RED, normal, uvRightBottom }); //11

        //Back
        normal = { 0, 0, -1 };
        AddVertex({ halfExtends * glm::vec3(1,  1, -1),  WHITE, normal, uvLeftTop }); //12
        AddVertex({ halfExtends * glm::vec3(-1,  1, -1), WHITE, normal, uvRightTop }); //13
        AddVertex({ halfExtends * glm::vec3(1, -1, -1),  WHITE, normal, uvLeftBottom }); //14
        AddVertex({ halfExtends * glm::vec3(-1, -1, -1), WHITE, normal, uvRightBottom }); //15

        //Left
        normal = { -1, 0, 0 };
        AddVertex({ halfExtends * glm::vec3(-1,  1, -1), WHITE, normal, uvLeftTop }); //16
        AddVertex({ halfExtends * glm::vec3(-1,  1, 1),  WHITE, normal, uvRightTop }); //17
        AddVertex({ halfExtends * glm::vec3(-1, -1, -1), WHITE, normal, uvLeftBottom }); //18
        AddVertex({ halfExtends * glm::vec3(-1, -1, 1),  WHITE, normal, uvRightBottom }); //19

        //Right
        normal = { 1, 0, 0 };
        AddVertex({ halfExtends * glm::vec3(1,  1,  1), WHITE, normal, uvLeftTop }); //20
        AddVertex({ halfExtends * glm::vec3(1,  1, -1), WHITE, normal, uvRightTop }); //21
        AddVertex({ halfExtends * glm::vec3(1, -1,  1), WHITE, normal, uvLeftBottom }); //22
        AddVertex({ halfExtends * glm::vec3(1, -1, -1), WHITE, normal, uvRightBottom });  //23
    }

    void GenerateIndices()
    {
        mIndices.reserve(36);
        //Top
        AddIndex(0, 2, 1);
        AddIndex(2, 3, 1);

        //Bottom
        AddIndex(4, 6, 5);
        AddIndex(6, 7, 5);

        //Front
        AddIndex(8, 10, 9);
        AddIndex(10, 11, 9);

        //Back
        AddIndex(12, 14, 13);
        AddIndex(13, 14, 15);

        //Left
        AddIndex(16, 18, 17);
        AddIndex(17, 18, 19);

        //Right
        AddIndex(20, 22, 21);
        AddIndex(22, 23, 21);
    }

public:
    std::vector<Vertex> mVertices{};
    std::vector<unsigned int> mIndices{};
};