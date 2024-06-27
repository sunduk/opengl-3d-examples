#pragma once

#include "Example01.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "SimpleMesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Vertex.h"

// forward declaration.
struct GLFWwindow;
class GameObject;
class RenderWindow;
class Scene;

class Example12 : public Example01
{
public:
    enum class BasicShaderType
    {
        Color,
        Lambert,
        HalfLambert,
        Rim,
        Outline,
        Thickness
    };

public:
    Example12();
    virtual ~Example12();
    void RunWithParam(BasicShaderType shaderType);
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    bool CreateMaterial();
    void CreateScene();

    void InitializeCamera();
    void InitializeRenderFlags();
    void ClearBuffer();

    void UpdateCameraControl();
    unsigned int LoadTexture(const std::string& path);

private:
    BasicShaderType mShaderType{};

    bool mFirstMouseMovement{ true };
    glm::vec2 mLastMousePosition{};

    glm::vec3 mCameraBeginPosition{};
    float mCameraBeginZoom{};

    Shader mDefaultShader{};
    Material mDefaultMaterial{};
    Shader mOutlineShader{};

    unsigned int mRobotTextureId0{};

    Scene* mScene{};

    // shape.
    Mesh mSphereMesh{};
    GameObject* mSphereObject{};
};