#pragma once

#include "SceneManager.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager& SceneManager::GetInstance()
{
    static SceneManager singletonInstance;
    return singletonInstance;
}

SceneManager::~SceneManager()
{
    DestroyAllScenes();
}

Scene* SceneManager::CreateScene()
{
    ++mLastSceneId;
    Scene* newInstance = new Scene(mLastSceneId);
    mScenes[mLastSceneId] = newInstance;
    return newInstance;
}

void SceneManager::DestroyAllScenes()
{
    for (int i = 0; i < mScenes.size(); ++i)
    {
        delete mScenes[i];
    }

    mScenes.clear();
    mLastSceneId = 0;
}