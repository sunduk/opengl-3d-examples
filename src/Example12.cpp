#include "Example12.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/random.hpp"
#include "stb/stb_image.h"

#include "GameObject.h"
#include "Material.h"
#include "RenderWindow.h"
#include "ObjLoader.h"
#include "Scene.h"
#include "SceneManager.h"


Example12::Example12()
{
    mTitle = "Example12_Scene";
}

Example12::~Example12()
{
}

void Example12::RunWithParam(BasicShaderType shaderType)
{
    mShaderType = shaderType;

    Example01::Run();
}

void Example12::Initialize()
{
    CreateMaterial();
    CreateScene();
    InitializeCamera();
    InitializeRenderFlags();
    SetCursorVisible(false);
}

void Example12::CleanUp()
{
    glDeleteBuffers(1, &mRobotTextureId0);
}

bool Example12::CreateMaterial()
{
    bool ret = false;
    switch (mShaderType)
    {
    case BasicShaderType::Color:
        ret = mDefaultShader.Load("../resources/shaders/Color.vs", "../resources/shaders/Color.fs");
        if (!ret)
        {
            return false;
        }

        mDefaultMaterial.SetShader(&mDefaultShader);
        mDefaultMaterial.SetPropertyVec3("customColor", glm::vec3(0, 1, 0));
        break;

    case BasicShaderType::Lambert:
        ret = mDefaultShader.Load("../resources/shaders/Lambert.vs", "../resources/shaders/Lambert.fs");
        if (!ret)
        {
            return false;
        }

        mDefaultMaterial.SetShader(&mDefaultShader);
        mDefaultMaterial.SetPropertyVec3("customColor", glm::vec3(0, 1, 0));
        break;

    case BasicShaderType::HalfLambert:
        ret = mDefaultShader.Load("../resources/shaders/HalfLambert.vs", "../resources/shaders/HalfLambert.fs");
        if (!ret)
        {
            return false;
        }

        mDefaultMaterial.SetShader(&mDefaultShader);
        mDefaultMaterial.SetPropertyVec3("customColor", glm::vec3(0, 1, 0));
        break;

    case BasicShaderType::Rim:
        ret = mDefaultShader.Load("../resources/shaders/Rim.vs", "../resources/shaders/Rim.fs");
        if (!ret)
        {
            return false;
        }

        mDefaultMaterial.SetShader(&mDefaultShader);
        mDefaultMaterial.SetPropertyVec3("customColor", glm::vec3(0, 1, 0));
        break;

    case BasicShaderType::Outline:
        ret = mDefaultShader.Load("../resources/shaders/HalfLambert.vs", "../resources/shaders/HalfLambert.fs");
        if (!ret)
        {
            return false;
        }

        mDefaultMaterial.SetShader(&mDefaultShader);
        mDefaultMaterial.SetPropertyVec3("customColor", glm::vec3(0, 1, 0));

        ret = mOutlineShader.Load("../resources/shaders/Outline.vs", "../resources/shaders/Outline.fs");
        if (!ret)
        {
            return false;
        }

        mOutlineShader.SetBackfaceCulling(false);
        mDefaultMaterial.SetShader2(&mOutlineShader);
        mDefaultMaterial.SetPropertyVec3("outlineColor", glm::vec3(0, 0, 0));
        break;

    case BasicShaderType::Thickness:
        ret = mDefaultShader.Load("../resources/shaders/Thickness.vs", "../resources/shaders/Thickness.fs");
        if (!ret)
        {
            return false;
        }

        mRobotTextureId0 = LoadTexture("../resources/models/policeman/palette.png");
        mDefaultMaterial.AddTexture(mRobotTextureId0);
        mDefaultMaterial.SetShader(&mDefaultShader);
        break;
    }

    return true;
}

void Example12::CreateScene()
{
    mScene = SceneManager::GetInstance().CreateScene();

    switch (mShaderType)
    {
    case BasicShaderType::Thickness:
    {
        ObjLoader objSphere("../resources/models/policeman/policeman.obj");
        mSphereMesh.Initialize(objSphere.mVertices, objSphere.mIndices);
    }
    break;

    default:
    {
        ObjLoader objSphere("../resources/models/shape/sphere.obj");
        mSphereMesh.Initialize(objSphere.mVertices, objSphere.mIndices);
    }
    break;
    }

    mSphereObject = mScene->CreateObject();
    mSphereObject->SetMesh(&mSphereMesh);
    mSphereObject->SetMaterial(&mDefaultMaterial);
    mSphereObject->mTransform.SetPosition(glm::vec3(0, 0, 0));

    mScene->GetDirectionalLight().GetTransform().SetEulerAnglesOnLocalAxis(glm::vec3(-45, 90, 0));
}

void Example12::InitializeCamera()
{
    Camera& mainCamera = mScene->GetCamera();
    mCameraBeginPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    mainCamera.SetPosition(mCameraBeginPosition);
    mainCamera.SetSpeed(2.0f);
    mCameraBeginZoom = 40.0f;
    mainCamera.SetZoome(mCameraBeginZoom);
}

void Example12::InitializeRenderFlags()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Example12::ClearBuffer()
{
    glfwMakeContextCurrent(mGlfwWindow);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Example12::Render()
{
    UpdateCameraControl();

    if (BasicShaderType::Thickness == mShaderType)
    {
        float sinValue = glm::sin(mElapsedTime);
        float a = -0.02f;
        float b = 0.08f;
        float t = (sinValue + 1.0f) * 0.5f;
        float thickness = a + (b - a) * t;
        mDefaultMaterial.SetPropertyFloat("thickness", thickness);
        mElapsedTime += mDeltaTime;
    }

    mScene->Update(mWindowParam.width, mWindowParam.height, mDeltaTime);
}

void Example12::UpdateCameraControl()
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

unsigned int Example12::LoadTexture(const std::string& path)
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