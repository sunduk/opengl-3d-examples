#pragma once

#include "Example01.h"

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

enum class UvType
{
    Fit,
    Smaller,
    Bigger,
};

class Example04 : public Example01
{
public:
    Example04();
    virtual ~Example04();
    void RunWithParam(UvType uvType, int wrapType, int filterType);
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    // 셰이더 관련.
    void CreateDefaultShader();
    void CheckShaderCompileErrors(unsigned int shader, std::string type);
    void DeleteDefaultShader();

    // 사각형 렌더링 관련.
    void CreateRectangle();
    void CreateVertexBuffer();
    void DeleteVertexBuffer();

    // 텍스쳐 관련.
    unsigned int LoadTexture(const std::string& path);

private:
    struct VertexUV
    {
        glm::vec3 mPosition{ 0,0,0 };
        glm::vec3 mColor{ 0,0,0 };
        glm::vec2 mUV{ 0,0 };

        VertexUV()
        {
        }

        VertexUV(const glm::vec3& position, const glm::vec3& color, const glm::vec2& uv)
        {
            mPosition = position;
            mColor = color;
            mUV = uv;
        }
    };

    UvType mUVType{};
    int mWrapType{};
    int mFilterType{};

    // 삼각형의 버텍스와 인덱스를 보관할 메모리 배열.
    std::vector<VertexUV> mVertices{};
    std::vector<unsigned int> mIndices{};

    // OpenGL에서 생성한 버퍼 ID를 보관할 변수들.
    unsigned int mVertexArrayObjectId{};
    unsigned int mVertexBufferObjectId{};
    unsigned int mElementBufferObjectId{};
    unsigned int mTextureId0{};
    unsigned int mTextureId1{};

    // OpenGL에서 사용하는 셰이더 ID를 보관할 변수.
    unsigned int mDefaultShaderID{};
};