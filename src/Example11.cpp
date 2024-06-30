#include "Example11.h"

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


Example11::Example11()
{
    mTitle = "Example11_Scene";
}

Example11::~Example11()
{
}

void Example11::Initialize()
{
    CreateMaterial();
    CreateScene();
    InitializeCamera();
    InitializeRenderFlags();
    SetCursorVisible(false);
}

void Example11::CleanUp()
{
    glDeleteBuffers(1, &mTextureId0);
    glDeleteBuffers(1, &mRobotTextureId0);
    glDeleteBuffers(1, &mDiceTextureId0);
}

bool Example11::CreateMaterial()
{
    bool ret = mLambertTextureShader.Load("../resources/shaders/LambertTexture.vs", "../resources/shaders/LambertTexture.fs");
    if (!ret)
    {
        return false;
    }

    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mDefaultMaterial.AddTexture(mTextureId0);
    mDefaultMaterial.SetShader(&mLambertTextureShader);

    mRobotTextureId0 = LoadTexture("../resources/models/robot/main_texture.png");
    mRobotMaterial.AddTexture(mRobotTextureId0);
    mRobotMaterial.SetShader(&mLambertTextureShader);

    mDiceTextureId0 = LoadTexture("../resources/models/dice/dice_dot.png");
    mDiceMaterial.AddTexture(mDiceTextureId0);
    mDiceMaterial.SetShader(&mLambertTextureShader);

    mPolicemanTextureId0 = LoadTexture("../resources/models/policeman/palette.png");
    mPolicemanMaterial.AddTexture(mPolicemanTextureId0);
    mPolicemanMaterial.SetShader(&mLambertTextureShader);

    return true;
}

void Example11::CreateScene()
{
    mScene = SceneManager::GetInstance().CreateScene();

    ObjLoader objRobot2("../resources/models/robot/robot2.obj");
    mRobotMesh.Initialize(objRobot2.mVertices, objRobot2.mIndices);
    mRobot = mScene->CreateObject();
    mRobot->SetMesh(&mRobotMesh);
    mRobot->SetMaterial(&mRobotMaterial);
    mRobot->mTransform.SetPosition(glm::vec3(-3, 0, 0));
    mRobot->mTransform.SetEulerAnglesOnLocalAxis(glm::vec3(0, 35.0f, 0));

    ObjLoader objRobot3("../resources/models/robot/robot3.obj");
    mRobotMesh2.Initialize(objRobot3.mVertices, objRobot3.mIndices);
    mRobot2 = mScene->CreateObject();
    mRobot2->SetMesh(&mRobotMesh2);
    mRobot2->SetMaterial(&mRobotMaterial);
    mRobot2->mTransform.SetPosition(glm::vec3(3, 0, 0));
    mRobot2->mTransform.SetEulerAnglesOnLocalAxis(glm::vec3(0, -35.0f, 0));

    ObjLoader objDice("../resources/models/dice/dice01.obj");
    mDiceMesh.Initialize(objDice.mVertices, objDice.mIndices);
    mDice = mScene->CreateObject();
    mDice->SetMesh(&mDiceMesh);
    mDice->SetMaterial(&mDiceMaterial);
    mDice->mTransform.SetPosition(glm::vec3(0, 0, 3));
    mDice->mTransform.SetEulerAnglesOnLocalAxis(glm::vec3(0, 0.0f, 0));

    ObjLoader objPoliceman("../resources/models/policeman/policeman.obj");
    mPolicemanMesh.Initialize(objPoliceman.mVertices, objPoliceman.mIndices);
    mPoliceman = mScene->CreateObject();
    mPoliceman->SetMesh(&mPolicemanMesh);
    mPoliceman->SetMaterial(&mPolicemanMaterial);
    mPoliceman->mTransform.SetPosition(glm::vec3(0, 0, -5));
    mPoliceman->mTransform.SetScale(glm::vec3(2.5f, 2.5f, 2.5f));
    mPoliceman->mTransform.SetEulerAnglesOnLocalAxis(glm::vec3(0, -25.0f, 0));

    mScene->GetDirectionalLight().GetTransform().SetEulerAnglesOnLocalAxis(glm::vec3(-20, 10, 0));
}

void Example11::InitializeCamera()
{
    Camera& mainCamera = mScene->GetCamera();
    mCameraBeginPosition = glm::vec3(0.0f, 7.0f, 10.0f);
    mainCamera.SetPosition(mCameraBeginPosition);
    mainCamera.AddPitch(-30.0f);
    mainCamera.SetSpeed(10.0f);
    mCameraBeginZoom = 60.0f;
    mainCamera.SetZoome(mCameraBeginZoom);
}

void Example11::InitializeRenderFlags()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Example11::ClearBuffer()
{
    glfwMakeContextCurrent(mGlfwWindow);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Example11::Render()
{
    UpdateCameraControl();
    mScene->Update(mWindowParam.width, mWindowParam.height, mDeltaTime);
}

void Example11::UpdateCameraControl()
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

unsigned int Example11::LoadTexture(const std::string& path)
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