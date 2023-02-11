#include "RenderWindow.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
    DestroyWindow();
}

GLFWwindow* RenderWindow::CreateWindow(int width, int height, std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, OnGlfwSetFramebufferSizeCallback);
    glfwSetCursorPosCallback(window, OnGlfwSetCursorPosCallback);
    glfwSetScrollCallback(window, OnGlfwSetScrollCallback);
    glfwSetKeyCallback(window, OnGlfwSetKeyCallback);

    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEPTH_TEST);
    mWindow = window;
    mWindowParam.width = width;
    mWindowParam.height = height;
    return window;
}

GLFWwindow* RenderWindow::GetGlfwWindow()
{
    return mWindow;
}

void RenderWindow::DestroyWindow()
{
    glfwTerminate();
}

void RenderWindow::SetCursorVisible(bool visible)
{
    if (visible)
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

bool RenderWindow::GetKeyState(int key)
{
    if (mKeyState.find(key) != mKeyState.end())
    {
        return mKeyState[key];
    }

    return false;
}

glm::vec2 RenderWindow::GetMouseWheelOffset()
{
    return mMouseWheelOffset;
}

void RenderWindow::ResetMouseWheelOffset()
{
    mMouseWheelOffset = glm::vec2(0);
}

glm::vec2 RenderWindow::GetCurrentMousePosition()
{
    return mMousePosition;
}

// Static callback functions.
void RenderWindow::OnGlfwSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    RenderWindow* renderWindow = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
    renderWindow->OnKeyInput(key, scancode, action, mods);
}

void RenderWindow::OnGlfwSetCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    RenderWindow* renderWindow = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
    renderWindow->OnMousePositionChanged(xpos, ypos);
}

void RenderWindow::OnGlfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    RenderWindow* renderWindow = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
    renderWindow->OnFramebufferSizeChanged(width, height);
}

void RenderWindow::OnGlfwSetScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    RenderWindow* renderWindow = static_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
    renderWindow->OnMouseWheelChanged(xoffset, yoffset);
}

// Example callback member functions.
void RenderWindow::OnFramebufferSizeChanged(int width, int height)
{
    glViewport(0, 0, width, height);
    mWindowParam.width = width;
    mWindowParam.height = height;
}

void RenderWindow::OnMousePositionChanged(double xpos, double ypos)
{
    mMousePosition.x = static_cast<float>(xpos);
    mMousePosition.y = static_cast<float>(ypos);
}

void RenderWindow::OnMouseWheelChanged(double xoffset, double yoffset)
{
    mMouseWheelOffset.x = static_cast<float>(xoffset);
    mMouseWheelOffset.y = static_cast<float>(yoffset);
}

void RenderWindow::OnKeyInput(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        mKeyState[key] = true;
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(mWindow, true);
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        mKeyState[key] = false;
    }
}

const WindowParam& RenderWindow::GetWindowInfo()
{
    return mWindowParam;
}