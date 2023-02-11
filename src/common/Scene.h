#pragma once

#include <map>
#include "glm/glm.hpp"

#include "BoxShape.h"
#include "Camera.h"
#include "DirectionalLight.h"

// forward declaration.
class GameObject;

class Scene
{
public:
    explicit Scene(unsigned int sceneId);
    virtual ~Scene();
    unsigned int GetInstanceId();
    GameObject* CreateObject();
    void DestroyObject(GameObject* obj);
    GameObject* FindObject(unsigned int id);
    void Update(int width, int height, float deltaSec);
    Camera& GetCamera();

private:
    void ClearReservedObjects();
    void DestroyAllObjects();

public:
    BoxShape mBoxShape{};

private:
    unsigned int mInstanceId{};
    unsigned int mLastObjectId{};
    std::map<unsigned int, GameObject*> mObjects;
    std::map<unsigned int, bool> mReservedDestroyObjects{};

    Camera mCamera{};
    DirectionalLight mDirectionalLight{};
};