#pragma once

#include "Example01.h"

#include <vector>

#include "glm/glm.hpp"

#include "SimpleMesh.h"
#include "SimpleTransform.h"
#include "Vertex.h"

class Example09 : public Example01
{
public:
    enum class ProjectionType
    {
        Perspective,
        Ortho1,
        Ortho2,
    };

public:
    Example09();
    virtual ~Example09();
    void RunWithParam(ProjectionType projectionType);
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    // 셰이더 관련.
    bool LoadShaderFromFile(std::string vertexPath, std::string fragmentPath);
    void CreateDefaultShader();
    void CheckShaderCompileErrors(unsigned int shader, std::string type);
    void DeleteDefaultShader();

    // 텍스쳐 관련.
    unsigned int LoadTexture(const std::string& path);

private:
    ProjectionType mProjectionType{};

    // OpenGL에서 생성한 버퍼 ID를 보관할 변수들.
    unsigned int mTextureId0{};
    unsigned int mTextureId1{};

    // OpenGL에서 사용하는 셰이더 ID를 보관할 변수.
    unsigned int mDefaultShaderID{};

    SimpleMesh mMesh{};
    SimpleTransform mTransform{};
};