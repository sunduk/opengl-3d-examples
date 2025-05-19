#include "Example10.h"

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


Example10::Example10()
{
    mTitle = "Example10_Scene";
}

Example10::~Example10()
{
}

void Example10::Initialize()
{
    CreateMaterial();
    CreateScene();
    InitializeCamera();
    InitializeRenderFlags();
    SetCursorVisible(false);
}

void Example10::CleanUp()
{
    glDeleteBuffers(1, &mTextureId0);
}

bool Example10::CreateMaterial()
{
    bool ret = mLambertTextureShader.Load("../resources/shaders/LambertTexture.vs", "../resources/shaders/LambertTexture.fs");
    if (!ret)
    {
        return false;
    }

    mDefaultMaterial.SetShader(&mLambertTextureShader);

    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mDefaultMaterial.AddTexture(mTextureId0);

    mPolicemanTextureId0 = LoadTexture("../resources/models/policeman/palette.png");
    mPolicemanMaterial.AddTexture(mPolicemanTextureId0);
    mPolicemanMaterial.SetShader(&mLambertTextureShader);

    return true;
}

void Example10::CreateScene()
{
    mScene = SceneManager::GetInstance().CreateScene();
    mBoxMesh.Initialize(mScene->mBoxShape.GetVertices(), mScene->mBoxShape.GetIndices());

    CreatePoliceman();
    CreatePyramid();
}

void Example10::CreatePoliceman()
{
    ObjLoader objPoliceman("../resources/models/policeman/policeman.obj");
    mPolicemanMesh.Initialize(objPoliceman.mVertices, objPoliceman.mIndices);
    mPoliceman = mScene->CreateObject();
    mPoliceman->SetMesh(&mPolicemanMesh);
    mPoliceman->SetMaterial(&mPolicemanMaterial);
    mPoliceman->mTransform.SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
    mPoliceman->mTransform.SetScale(glm::vec3(4.5f, 4.5f, 4.5f));
}

void Example10::CreatePyramid()
{
    int boxCount = 11;
    float y = -10.0f;
    while (boxCount >= 1)
    {
        for (int row = 0; row < boxCount; ++row)
        {
            for (int col = 0; col < boxCount; ++col)
            {
                GameObject* box = mScene->CreateObject();
                box->SetMaterial(&mDefaultMaterial);
                box->SetMesh(&mBoxMesh);
                float x = col * 2.0f - ((boxCount - 1) * 0.5f * 2.0f);
                float z = row * 2.0f - ((boxCount - 1) * 0.5f * 2.0f);
                box->mTransform.SetPosition(glm::vec3(x, y, z));
            }
        }

        boxCount -= 2;
        y += 2.0f;
    }
}

void Example10::InitializeCamera()
{
    Camera& mainCamera = mScene->GetCamera();
    mCameraBeginPosition = glm::vec3(0.0f, 0.0f, 20.0f);
    mainCamera.SetPosition(mCameraBeginPosition);
    mainCamera.SetSpeed(10.0f);
    mCameraBeginZoom = 60.0f;
    mainCamera.SetZoome(mCameraBeginZoom);
}

void Example10::InitializeRenderFlags()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Example10::ClearBuffer()
{
    glfwMakeContextCurrent(mGlfwWindow);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Example10::Render()
{
    mPoliceman->mTransform.RotateOnLocalAxis(glm::normalize(glm::vec3(0, 1, 0)) * 90.0f * mDeltaTime);

    UpdateCameraControl();
    mScene->Update(mWindowParam.width, mWindowParam.height, mDeltaTime);
}

void Example10::UpdateCameraControl()
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

unsigned int Example10::LoadTexture(const std::string& path)
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