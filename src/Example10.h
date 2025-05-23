﻿#pragma once

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

class Example10 : public Example01
{
public:
    Example10();
    virtual ~Example10();
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    bool CreateMaterial();
    void CreateScene();

    void CreatePoliceman();
    void CreatePyramid();

    void InitializeCamera();
    void InitializeRenderFlags();
    void ClearBuffer();

    void UpdateCameraControl();
    unsigned int LoadTexture(const std::string& path);

private:
    bool mFirstMouseMovement{ true };
    glm::vec2 mLastMousePosition{};

    glm::vec3 mCameraBeginPosition{};
    float mCameraBeginZoom{};

    unsigned int mTextureId0{};
    Shader mLambertTextureShader{};
    Material mDefaultMaterial{};
    Mesh mBoxMesh{};

    Scene* mScene{};

    // policeman.
    Mesh mPolicemanMesh{};
    GameObject* mPoliceman{};

    unsigned int mPolicemanTextureId0{};
    Material mPolicemanMaterial{};
};