#pragma once

#include <map>
#include <string>

#include "glm/glm.hpp"

#include "GameObject.h"
#include "WindowParam.h"

// forward declaration.
struct GLFWwindow;

class RenderWindow
{
public:
    RenderWindow();
    virtual ~RenderWindow();
    GLFWwindow* CreateWindow(int width, int height, std::string title);
    GLFWwindow* GetGlfwWindow();
    void DestroyWindow();
    void SetCursorVisible(bool visible);
    bool GetKeyState(int key);
    glm::vec2 GetMouseWheelOffset();
    void ResetMouseWheelOffset();
    glm::vec2 GetCurrentMousePosition();
    const WindowParam& GetWindowInfo();

private:
    static void OnGlfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void OnGlfwSetCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void OnGlfwSetScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void OnGlfwSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void OnFramebufferSizeChanged(int width, int height);
    void OnMousePositionChanged(double xpos, double ypos);
    void OnMouseWheelChanged(double xoffset, double yoffset);
    void OnKeyInput(int key, int scancode, int action, int mods);

private:
    GLFWwindow* mWindow{};
    WindowParam mWindowParam{};

    std::map<int, bool> mKeyState{};
    glm::vec2 mMousePosition{};
    glm::vec2 mMouseWheelOffset{};
};