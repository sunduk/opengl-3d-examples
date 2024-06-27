#pragma once

#include "Example01.h"

#include <vector>

#include "glm/glm.hpp"

class Example00 : public Example01
{
public:
    Example00();
    virtual ~Example00();
    virtual void Initialize() override;
	virtual void Render() override;
    virtual void CleanUp() override;

private:
    // 셰이더 관련.
    void CreateDefaultShader();
    void CheckShaderCompileErrors(unsigned int shader, std::string type);
    void DeleteDefaultShader();

    // 삼각형 렌더링 관련.
    void CreateTriangle();
    void CreateVertexBuffer();
    void DeleteVertexBuffer();

private:
    // 삼각형의 버텍스와 인덱스를 보관할 메모리 배열.
    std::vector<glm::vec3> mVertices{};
    std::vector<unsigned int> mIndices{};

    // OpenGL에서 생성한 버퍼 ID를 보관할 변수들.
    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
    unsigned int mElementBufferObjectId{};

    // OpenGL에서 사용하는 셰이더 ID를 보관할 변수.
    unsigned int mDefaultShaderID{};
};