#pragma once

#include "Scene.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GameObject.h"
#include "Shader.h"

Scene::Scene(unsigned int sceneId)
    : mInstanceId(sceneId)
{
    mCamera.SetPosition(glm::vec3(0, 0, 100));
}

Scene::~Scene()
{
    DestroyAllObjects();
}

void Scene::ClearReservedObjects()
{
    for (const auto& element : mReservedDestroyObjects)
    {
        unsigned int objectInstanceId = element.first;
        delete mObjects[objectInstanceId];
        mObjects.erase(objectInstanceId);
    }
    mReservedDestroyObjects.clear();
}

void Scene::DestroyAllObjects()
{
    for (const auto& element : mObjects)
    {
        unsigned int objectInstanceId = element.first;
        delete mObjects[objectInstanceId];
    }
    mObjects.clear();
}

unsigned int Scene::GetInstanceId()
{
    return mInstanceId;
}

GameObject* Scene::CreateObject()
{
    ++mLastObjectId;
    GameObject* newInstance = new GameObject(mLastObjectId);
    mObjects[mLastObjectId] = newInstance;
    return newInstance;
}

void Scene::DestroyObject(GameObject* obj)
{
    mReservedDestroyObjects[obj->GetInstanceId()] = true;
}

GameObject* Scene::FindObject(unsigned int id)
{
    if (mObjects.find(id) == mObjects.end())
    {
        return nullptr;
    }

    return mObjects[id];
}

void Scene::Update(int width, int height, float deltaSec)
{
    mCamera.Update(deltaSec);

    /*glm::vec3 color = mDirectionalLight.GetColor();
    color = color - 0.1f * deltaSec;
    mDirectionalLight.SetColor(color);*/

    //mDirectionalLight.mTransform.RotateOnWorldAxis(glm::vec3(0.0f, 1.0f, 0.0f) * (45.0f * deltaSec));

    ShaderParam matrixParam{};
    float fov = glm::radians(mCamera.GetZoom());
    matrixParam.projectionMatrix = glm::perspective(fov, (float)width / (float)height, 0.1f, 1000.0f);

    // ortho.
    /*float size = 2.0f;
    float windowWidth = static_cast<float>(width);
    float windowHeight = static_cast<float>(height);
    float ratio = size / windowHeight;
    float horizontalSize = ratio * windowWidth;
    float near = 0.1f;
    float far = 1000.0f;
    matrixParam.projectionMatrix = glm::ortho(-horizontalSize, horizontalSize, -size, size, near, far);*/

    matrixParam.viewMatrix = mCamera.GetViewMatrix();
    matrixParam.viewProjectionMatrix = matrixParam.projectionMatrix * matrixParam.viewMatrix;

    matrixParam.lightDir = glm::normalize(mDirectionalLight.GetDirection());
    matrixParam.lightColor = mDirectionalLight.GetColor();

    matrixParam.cameraWorldPosition = mCamera.GetPosition();

    for (const auto& element : mObjects)
    {
        element.second->Update(matrixParam, deltaSec);
    }

    ClearReservedObjects();
}

Camera& Scene::GetCamera()
{
    return mCamera;
}

DirectionalLight& Scene::GetDirectionalLight()
{
    return mDirectionalLight;
}