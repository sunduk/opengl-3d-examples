#include "Example13.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/random.hpp"
#include "stb/stb_image.h"

#include "Bezier.h"
#include "BezierSpline.h"
#include "CatmullRomSpline.h"
#include "GameObject.h"
#include "Hermite.h"
#include "HermiteSpline.h"
#include "Line.h"
#include "Material.h"
#include "RenderWindow.h"
#include "ObjLoader.h"
#include "Scene.h"
#include "SceneManager.h"


Example13::Example13()
{
    mTitle = "Example13_Scene";
}

Example13::~Example13()
{
}

void Example13::RunWithParam(CurveType curveType)
{
    mCurveType = curveType;

    Example01::Run();
}

void Example13::Initialize()
{
    CreateMaterial();
    CreateScene();
    InitializeRenderFlags();
    SetCursorVisible(false);
}

void Example13::CleanUp()
{
    glDeleteBuffers(1, &mRobotTextureId0);
}

bool Example13::CreateMaterial()
{
    bool ret = mDefaultShader.Load("../resources/shaders/VertexColor.vs", "../resources/shaders/VertexColor.fs");
    if (!ret)
    {
        return false;
    }

    mLineMaterial.SetShader(&mDefaultShader);


    ret = mColorShader.Load("../resources/shaders/Color.vs", "../resources/shaders/Color.fs");
    if (!ret)
    {
        return false;
    }
    mLineShapeMaterial.SetShader(&mColorShader);

    return true;
}

void Example13::CreateScene()
{
    bool useThickLine = true;

    mScene = SceneManager::GetInstance().CreateScene();
    InitializeCamera();

    ObjLoader objSphere("../resources/models/shape/sphere.obj");
    mSphereMesh.Initialize(objSphere.mVertices, objSphere.mIndices);

    switch (mCurveType)
    {
    case CurveType::BezierCurve:
    {
        // 3차 베지에 곡선.
        glm::vec3 begin = glm::vec3(-2, 0, 0);
        glm::vec3 controlPoint0 = glm::vec3(-1, 3, 0);
        glm::vec3 controlPoint1 = glm::vec3(1, -2, 0);
        glm::vec3 end = glm::vec3(1, 3, 0);

        Bezier bezier;
        bezier.Add(begin, controlPoint0, controlPoint1, end);

        // Sphere.
        GameObject* beginObj = mScene->CreateObject();
        beginObj->SetMesh(&mSphereMesh);
        beginObj->SetMaterial(&mLineMaterial);
        beginObj->mTransform.SetPosition(begin);
        beginObj->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

        GameObject* endObj = mScene->CreateObject();
        endObj->SetMesh(&mSphereMesh);
        endObj->SetMaterial(&mLineMaterial);
        endObj->mTransform.SetPosition(end);
        endObj->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

        GameObject* controlPointObj0 = mScene->CreateObject();
        controlPointObj0->SetMesh(&mSphereMesh);
        controlPointObj0->SetMaterial(&mLineMaterial);
        controlPointObj0->mTransform.SetPosition(controlPoint0);
        controlPointObj0->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

        GameObject* controlPointObj1 = mScene->CreateObject();
        controlPointObj1->SetMesh(&mSphereMesh);
        controlPointObj1->SetMaterial(&mLineMaterial);
        controlPointObj1->mTransform.SetPosition(controlPoint1);
        controlPointObj1->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

        // thick line.
        LineShape lineShape(begin);

        std::vector<Vertex> lines;
        glm::vec3 prev = begin;
        for (int i = 1; i <= 20; ++i)
        {
            glm::vec3 pos = bezier.Evaluate(i / 20.0f);

            // thin line.
            lines.push_back({ prev , glm::vec3(1,0,0) });
            lines.push_back({ pos, glm::vec3(1,0,0) });
            prev = pos;

            // thick line.
            lineShape.AddPosition(pos);

            // Sphere.
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineMaterial);
            sphere->mTransform.SetPosition(pos);
            sphere->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
        }

        mLine.Initialize(lines);

        // thick line.
        mLineMesh.Initialize(lineShape.mVertices, lineShape.mIndices);
    }
    break;

    case CurveType::BezierSpline:
    {
        std::vector<glm::vec3> positions;

        glm::vec3 begin = glm::vec3(0, 0, 0);
        glm::vec3 end = glm::vec3(6, -3, -5);
        // bezier 1.
        glm::vec3 v0 = begin;
        glm::vec3 v1 = glm::vec3(2, 3, 0);
        glm::vec3 v2 = glm::vec3(-2, 2, 0);
        glm::vec3 v3 = glm::vec3(2, 0, 0);
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);
        positions.push_back(v3);

        // points.
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v0);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v3);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }

        // bezier 2.
        v0 = v3;
        v1 = v0 + (v3 - v2);
        v2 = v1 + glm::vec3(2, 3, 0);
        v3 = glm::vec3(5, 0, -2);
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);
        positions.push_back(v3);

        // points.
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v0);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v3);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }

        // bezier 3.
        v0 = v3;
        v1 = v0 + (v3 - v2);
        v2 = v1 + glm::vec3(3, 0, -3);
        v3 = end;
        positions.push_back(v0);
        positions.push_back(v1);
        positions.push_back(v2);
        positions.push_back(v3);

        // points.
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v0);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v3);
            sphere->mTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        }

        // bezier 1 + bezier 2 + bezier 3 = bezier spline.
        BezierSpline spline;
        for (const auto& v : positions)
        {
            spline.Add(v);
        }

        // thick line.
        LineShape lineShape(begin);

        glm::vec3 prevPos = begin;
        std::vector<Vertex> lines;
        for (int i = 1; i <= 60; ++i)
        {
            glm::vec3 pos = spline.Evaluate(i / 60.0f);

            lines.push_back({ prevPos, glm::vec3(1,0,0) });
            lines.push_back({ pos, glm::vec3(1,0,0) });
            prevPos = pos;

            // thick line.
            lineShape.AddPosition(pos);
        }

        mLine.Initialize(lines);

        Camera& mainCamera = mScene->GetCamera();
        mCameraBeginPosition = glm::vec3(3.0f, 1.0f, 10.0f);
        mainCamera.SetPosition(mCameraBeginPosition);

        // thick line.
        mLineMesh.Initialize(lineShape.mVertices, lineShape.mIndices);
    }
    break;

    case CurveType::HermiteCurve:
    {
        glm::vec3 begin = glm::vec3(0, 0, 0);
        glm::vec3 tangentU = glm::vec3(0, -2, 0);
        glm::vec3 end = glm::vec3(2, 0, 0);
        glm::vec3 tangentV = glm::vec3(0, -2, 0);

        Hermite hermite;
        hermite.Set(begin, tangentU, end, tangentV);

        // thick line.
        LineShape lineShape(begin);

        glm::vec3 prevPos = begin;
        std::vector<Vertex> lines;
        for (int i = 1; i <= 20; ++i)
        {
            glm::vec3 pos = hermite.Evaluate(i / 20.0f);

            // thin line.
            lines.push_back({ prevPos, glm::vec3(1,0,0) });
            lines.push_back({ pos, glm::vec3(1,0,0) });
            prevPos = pos;

            // thick line.
            lineShape.AddPosition(pos);

            // Sphere.
            /*GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mDefaultMaterial);
            sphere->mTransform.SetPosition(pos);
            sphere->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));*/
        }

        mLine.Initialize(lines);

        // thick line.
        mLineMesh.Initialize(lineShape.mVertices, lineShape.mIndices);

        // debugging.
        /*std::vector<Vertex> debugLineVertices;
        debugLineVertices.push_back({ begin, glm::vec3(1,0,0) });
        debugLineVertices.push_back({ begin + tangentU, glm::vec3(1,0,0) });
        mDebugLine0.Initialize(debugLineVertices);

        GameObject* objDebug = mScene->CreateObject();
        objDebug->SetLine(&mDebugLine0);
        objDebug->SetMaterial(&mLineMaterial);
        objDebug->mTransform.SetPosition(glm::vec3(0, 0, 0));


        debugLineVertices.clear();
        debugLineVertices.push_back({ end, glm::vec3(1,0,0) });
        debugLineVertices.push_back({ end + tangentV, glm::vec3(1,0,0) });
        mDebugLine1.Initialize(debugLineVertices);

        GameObject* objDebug2 = mScene->CreateObject();
        objDebug2->SetLine(&mDebugLine1);
        objDebug2->SetMaterial(&mLineMaterial);
        objDebug2->mTransform.SetPosition(glm::vec3(0, 0, 0));*/
    }
    break;

    case CurveType::HermiteSpline:
    {
        glm::vec3 begin = glm::vec3(0, 0, 0);
        glm::vec3 end = glm::vec3(2, 0, 2);

        HermiteSpline hermiteSpline;
        hermiteSpline.Add(begin, glm::vec3(7, 3, 0));
        hermiteSpline.Add(glm::vec3(4, 0, 0), glm::vec3(5, -3, 0));
        hermiteSpline.Add(glm::vec3(0, -2, 2), glm::vec3(-5, 2, 0));
        hermiteSpline.Add(end, glm::vec3(0, -5, 0));

        // tangent vectors.
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(begin + glm::vec3(7, 3, 0));
            sphere->mTransform.SetScale(glm::vec3(0.1, 0.1, 0.1));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(glm::vec3(4, 0, 0) + glm::vec3(5, -3, 0));
            sphere->mTransform.SetScale(glm::vec3(0.1, 0.1, 0.1));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(glm::vec3(0, -2, 2) + glm::vec3(-5, 2, 0));
            sphere->mTransform.SetScale(glm::vec3(0.1, 0.1, 0.1));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(end + glm::vec3(0, -5, 0));
            sphere->mTransform.SetScale(glm::vec3(0.1, 0.1, 0.1));
        }

        // points.
        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(begin);
            sphere->mTransform.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(glm::vec3(4, 0, 0));
            sphere->mTransform.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(glm::vec3(0, -2, 2));
            sphere->mTransform.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
        }

        {
            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(end);
            sphere->mTransform.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
        }

        // thick line.
        LineShape lineShape(begin);

        glm::vec3 prevPos = begin;
        std::vector<Vertex> lines;
        for (int i = 1; i <= 100; ++i)
        {
            glm::vec3 pos = hermiteSpline.Evaluate(i / 100.0f);

            lines.push_back({ prevPos, glm::vec3(1,0,0) });
            lines.push_back({ pos, glm::vec3(1,0,0) });
            prevPos = pos;

            // thick line.
            lineShape.AddPosition(pos);

            // Sphere.
            /*GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(pos);
            sphere->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));*/
        }

        mLine.Initialize(lines);

        // thick line.
        mLineMesh.Initialize(lineShape.mVertices, lineShape.mIndices);

        Camera& mainCamera = mScene->GetCamera();
        mCameraBeginPosition = glm::vec3(1.0f, 0.0f, 20.0f);
        mainCamera.SetPosition(mCameraBeginPosition);
    }
    break;

    case CurveType::CatmullRomSpline:
    {
        std::vector<glm::vec3> points = {
            { 0.0f,   0.0f,  0.0f},
            { 5.0f,  -5.0f,  0.0f},
            {10.0f,  -1.5f,  0.0f},
            {15.0f,  -5.0f,  0.0f},
            {17.0f,   0.5f,  0.0f},
        };

        CatmullRomSpline catmullRomSpline;
        for (const auto& v : points)
        {
            catmullRomSpline.Add(v);

            GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(v);
            sphere->mTransform.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
        }

        // Cardinal spline.
        catmullRomSpline.SetTension(1.0f);

        // thick line.
        LineShape lineShape(points[0]);

        glm::vec3 prevPos = points[0];
        std::vector<Vertex> lines;
        for (int i = 1; i <= 100; ++i)
        {
            glm::vec3 pos = catmullRomSpline.Evaluate(i / 100.0f);

            lines.push_back({ prevPos, glm::vec3(1,0,0) });
            lines.push_back({ pos, glm::vec3(1,0,0) });
            prevPos = pos;

            // thick line.
            lineShape.AddPosition(pos);

            // Sphere.
            /*GameObject* sphere = mScene->CreateObject();
            sphere->SetMesh(&mSphereMesh);
            sphere->SetMaterial(&mLineShapeMaterial);
            sphere->mTransform.SetPosition(pos);
            sphere->mTransform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));*/
        }

        mLine.Initialize(lines);

        // thick line.
        mLineMesh.Initialize(lineShape.mVertices, lineShape.mIndices);

        Camera& mainCamera = mScene->GetCamera();
        mCameraBeginPosition = glm::vec3(8.0f, 0.0f, 30.0f);
        mainCamera.SetPosition(mCameraBeginPosition);
    }
    break;
    }

    GameObject* obj = mScene->CreateObject();
    if (useThickLine)
    {
        obj->SetMesh(&mLineMesh);
        obj->SetMaterial(&mLineShapeMaterial);
    }
    else
    {
        obj->SetLine(&mLine);
        obj->SetMaterial(&mLineMaterial);
    }
    obj->mTransform.SetPosition(glm::vec3(0, 0, 0));

    mScene->GetDirectionalLight().GetTransform().SetEulerAnglesOnLocalAxis(glm::vec3(-45, 90, 0));
}

void Example13::InitializeCamera()
{
    Camera& mainCamera = mScene->GetCamera();
    mCameraBeginPosition = glm::vec3(0.0f, 1.0f, 10.0f);
    mainCamera.SetPosition(mCameraBeginPosition);
    mainCamera.SetSpeed(2.0f);
    mCameraBeginZoom = 40.0f;
    mainCamera.SetZoome(mCameraBeginZoom);
}

void Example13::InitializeRenderFlags()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Example13::Render()
{
    UpdateCameraControl();
    //mScene->GetDirectionalLight().GetTransform().RotateOnWorldAxis(glm::vec3(0, 45 * mDeltaTime, 0));
    mScene->Update(mWindowParam.width, mWindowParam.height, mDeltaTime);
}

void Example13::UpdateCameraControl()
{
    // Camera movement.
    Camera& camera = mScene->GetCamera();
    camera.ResetMovement();
    if (GetKeyState(GLFW_KEY_W) || GetKeyState(GLFW_KEY_UP))
    {
        camera.AddMovement(Camera::MovementDirection::Forward);
    }
    else if (GetKeyState(GLFW_KEY_S) || GetKeyState(GLFW_KEY_DOWN))
    {
        camera.AddMovement(Camera::MovementDirection::Backward);
    }

    if (GetKeyState(GLFW_KEY_A) || GetKeyState(GLFW_KEY_LEFT))
    {
        camera.AddMovement(Camera::MovementDirection::Left);
    }
    else if (GetKeyState(GLFW_KEY_D) || GetKeyState(GLFW_KEY_RIGHT))
    {
        camera.AddMovement(Camera::MovementDirection::Right);
    }


    // Camera rotation.
    glm::vec2 mousePosition = GetCurrentMousePosition();
    float deltaX = mousePosition.x - mLastMousePosition.x;
    float deltaY = mousePosition.y - mLastMousePosition.y;
    if (glm::abs(deltaX) > 0 || glm::abs(deltaY) > 0)
    {
        if (mFirstMouseMovement)
        {
            mFirstMouseMovement = false;
            deltaX = 0.0f;
            deltaY = 0.0f;
        }

        float sensitive = 0.2f;
        camera.AddYaw(deltaX * sensitive);
        camera.AddPitch(-deltaY * sensitive);
    }
    mLastMousePosition = mousePosition;


    // Camera zoom.
    camera.SetMouseWheelOffset(GetMouseWheelOffset().y * 2.0f);
    ResetMouseWheelOffset();


    // Reset camera.
    if (GetKeyState(GLFW_KEY_R))
    {
        camera.SetPosition(mCameraBeginPosition);
        camera.SetZoome(mCameraBeginZoom);
        camera.ResetRotation();
    }
}

unsigned int Example13::LoadTexture(const std::string& path)
{
    unsigned int textureId{};
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // texture wrap.
    GLint wrapParam = GL_REPEAT;
    int wrapType = 0;
    switch (wrapType)
    {
    case 0:
        wrapParam = GL_REPEAT;
        break;

    case 1:
        wrapParam = GL_CLAMP_TO_EDGE;
        break;

    case 2:
        wrapParam = GL_MIRRORED_REPEAT;
        break;

    case 3:
        wrapParam = GL_CLAMP_TO_BORDER;
        float borderColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);

    // texture sampling.
    GLint samplingParam = GL_NEAREST;
    int samplingType = 0;
    switch (samplingType)
    {
    case 0:
        samplingParam = GL_NEAREST;
        break;

    case 1:
        samplingParam = GL_LINEAR;
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplingParam);

    // Load Texture.
    int width{};
    int height{};
    int channels{};
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (imageData)
    {
        switch (channels)
        {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            break;

        case 4:     // with alpha channel.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            break;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(imageData);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    return textureId;
}