#pragma once

#include "Example01.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include "BoxShape.h"
#include "Camera.h"
#include "GameObject.h"
#include "Line.h"
#include "LineShape.h"
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

class Example13 : public Example01
{
public:
    enum class CurveType
    {
        BezierCurve,
        BezierSpline,
        HermiteCurve,
        HermiteSpline,
        CatmullRomSpline
    };

public:
    Example13();
    virtual ~Example13();
    void RunWithParam(CurveType curveType);
    virtual void Initialize() override;
    virtual void Render() override;
    virtual void CleanUp() override;

private:
    bool CreateMaterial();
    void CreateScene();

    void InitializeCamera();
    void InitializeRenderFlags();

    void UpdateCameraControl();
    unsigned int LoadTexture(const std::string& path);

private:
    CurveType mCurveType{};

    bool mFirstMouseMovement{ true };
    glm::vec2 mLastMousePosition{};

    glm::vec3 mCameraBeginPosition{};
    float mCameraBeginZoom{};

    Shader mDefaultShader{};
    Shader mColorShader{};
    Shader mOutlineShader{};

    Material mLineMaterial{};
    Material mLineShapeMaterial{};

    unsigned int mRobotTextureId0{};

    Scene* mScene{};

    Mesh mSphereMesh{};
    Line mLine;

    Mesh mLineMesh{};

    Line mDebugLine0{};
    Line mDebugLine1{};
};