#pragma once

#include "Example01.h"

#include <vector>

#include "glm/glm.hpp"

#include "Vertex.h"

class Example05 : public Example01
{
public:
    enum class ShaderType
    {
        TextureColor,
        Invert,
        Grayscale,
        Add,
        Multiply,
        Lerp
    };

public:
    Example05();
    virtual ~Example05();
    void RunWithParam(ShaderType shaderType);
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    // 셰이더 관련.
    unsigned int CreateShader(const char* FRAGMENT_SHADER_CODE);
    unsigned int CreateTextureColorShader();
    unsigned int CreateInvertShader();
    unsigned int CreateGrayscaleShader();
    unsigned int CreateAddShader();
    unsigned int CreateMultipleyShader();
    unsigned int CreateLerpShader();
    void CheckShaderCompileErrors(unsigned int shader, std::string type);
    void DeleteDefaultShader();

    // 사각형 렌더링 관련.
    void CreateRectangle();
    void CreateVertexBuffer();
    void DeleteVertexBuffer();

    // 텍스쳐 관련.
    unsigned int LoadTexture(const std::string& path);

private:
    ShaderType mShaderType{};

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