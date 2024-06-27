#pragma once

#include "LineShape.h"

LineShape::LineShape(glm::vec3 begin)
{
    mBegin = begin;
    mLastIndexV1 = 0;
    mLastIndexV3 = 0;
}

LineShape::~LineShape()
{
}

void LineShape::AddPosition(glm::vec3 end)
{
    AddQuad(end);
    mBegin = end;
}

void LineShape::AddQuad(glm::vec3 end)
{
    mBegins.push_back(mBegin);
    glm::vec3 line1 = glm::normalize(end - mBegin);
    glm::vec3 line2 = glm::vec3(0, 0, 1);

    glm::vec3 line3 = glm::cross(line2, line1);
    line3 = glm::normalize(line3);

    float width = 0.02f;
    glm::vec3 v0 = mBegin + line3 * width;
    glm::vec3 v1 = end + line3 * width;
    glm::vec3 v2 = mBegin - line3 * width;
    glm::vec3 v3 = end - line3 * width;

    glm::vec3 vertexColor = glm::vec3(1, 1, 1);
    if (mVertices.empty())
    {
        // 첫번째 사각형 만들기.
        /*
        * v0      v1
        * +-------+
        * |      /|
        * |    /  |
        * |  /    |
        * |/      |
        * +-------+
        * v2      v3
        */

        // 버텍스 설정.
        mVertices.clear();
        mVertices.push_back({ v0, vertexColor });
        mVertices.push_back({ v1, vertexColor });
        mVertices.push_back({ v2, vertexColor });
        mVertices.push_back({ v3, vertexColor });

        // 인덱스 설정.
        mIndices.clear();
        mIndices.push_back(0);
        mIndices.push_back(2);
        mIndices.push_back(1);

        mIndices.push_back(2);
        mIndices.push_back(3);
        mIndices.push_back(1);

        // 이번 사각형의 경계 부분은 다음에 올 사각형의 시작 부분이므로 인덱스값을 저장해 놓는다.
        mLastIndexV1 = 1;
        mLastIndexV3 = 3;
    }
    else
    {
        // 기존 사각형에 버텍스 두개를 붙여 새로운 사각형을 만든다.
        /*
        *              v1
        * -----+-------+
        *     /|      /|
        *   /  |    /  |
        * /    |  /    |
        *      |/      |
        * -----+-------+
        *              v3
        */

        // 버텍스 설정.
        mVertices.push_back({ v1, vertexColor });
        mVertices.push_back({ v3, vertexColor });

        // 인덱스 설정.
        unsigned int currentIndexV1 = static_cast<unsigned int>(mVertices.size() - 2);
        unsigned int currentIndexV3 = static_cast<unsigned int>(mVertices.size() - 1);

        mIndices.push_back(mLastIndexV1);
        mIndices.push_back(mLastIndexV3);
        mIndices.push_back(currentIndexV1);

        mIndices.push_back(mLastIndexV3);
        mIndices.push_back(currentIndexV3);
        mIndices.push_back(currentIndexV1);

        mLastIndexV1 = currentIndexV1;
        mLastIndexV3 = currentIndexV3;
    }
}
