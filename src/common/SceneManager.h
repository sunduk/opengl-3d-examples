#pragma once

#include <map>

// forward declaration.
class Scene;

class SceneManager
{
public:
    static SceneManager& GetInstance();
    virtual ~SceneManager();
    Scene* CreateScene();
    void DestroyAllScenes();

private:
    explicit SceneManager();

    SceneManager(SceneManager const&) = delete;             // Copy construct
    SceneManager(SceneManager&&) = delete;                  // Move construct
    SceneManager& operator=(SceneManager const&) = delete;  // Copy assign
    SceneManager& operator=(SceneManager&&) = delete;      // Move assign

private:
    unsigned int mLastSceneId{};
    std::map<unsigned int, Scene*> mScenes;
};