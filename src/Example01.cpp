#include "Example01.h"

#include <iostream>
#include <string>
#include <thread>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Example01::Example01()
{
    mTitle = "Example01_Window";
}

Example01::~Example01()
{
}

GLFWwindow* Example01::CreateWindow(int width, int height, std::string title)
{
    mWindowParam.width = width;
    mWindowParam.height = height;

    // 윈도우 생성을 위한 준비를 한다.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 윈도우를 생성한다.
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        return nullptr;
    }

    // 생성한 윈도우를 작업 대상으로 설정한다.
    glfwMakeContextCurrent(window);

    // 이벤트를 받을 콜백 함수를 연결한다.
    glfwSetFramebufferSizeCallback(window, OnGlfwSetFramebufferSizeCallback);
    glfwSetCursorPosCallback(window, OnGlfwSetCursorPosCallback);
    glfwSetMouseButtonCallback(window, OnGlfwSetMouseButtonCallback);
    glfwSetScrollCallback(window, OnGlfwSetScrollCallback);
    glfwSetKeyCallback(window, OnGlfwSetKeyCallback);

    glfwSetWindowUserPointer(window, this);

    // OpenGL 드라이버 함수들을 연동한다.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return nullptr;
    }

    return window;
}

void Example01::Run()
{
    // 윈도우를 생성한다.
    mGlfwWindow = CreateWindow(800, 800, mTitle);
    if (nullptr == mGlfwWindow)
    {
        // 문제가 발생해서 종료하게 되는 경우.
        glfwTerminate();
        return;
    }

    Initialize();

    // 윈도우가 닫힐 때 까지 루프를 돌며 렌더링을 수행한다.
    while (!glfwWindowShouldClose(mGlfwWindow))
    {
        // 화면을 특정 색상으로 채운다.
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        // 컬러버퍼와 뎁스버퍼를 지운다.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mDeltaTime = static_cast<float>(glfwGetTime()) - mPrevTime;

        Render();

        mPrevTime = static_cast<float>(glfwGetTime());

        glfwSwapBuffers(mGlfwWindow);
        // 윈도우 이벤트를 감지한다.
        glfwPollEvents();

        // CPU점유율을 낮추기 위해 일정시간 대기한다.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    CleanUp();

    // 윈도우를 종료한다.
    glfwTerminate();
}

void Example01::Initialize()
{
    // 초기화 코드가 들어갈 영역.
    // ...
}

void Example01::Render()
{
    // 렌더링 코드가 들어갈 영역.
    // ...
}

void Example01::CleanUp()
{
    // 메모리 해제 코드가 들어갈 영역.
    // ...
}

void Example01::SetCursorVisible(bool visible)
{
    if (visible)
    {
        glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

bool Example01::GetKeyState(int key)
{
    if (mKeyState.find(key) != mKeyState.end())
    {
        return mKeyState[key];
    }

    return false;
}

glm::vec2 Example01::GetMouseWheelOffset()
{
    return mMouseWheelOffset;
}

void Example01::ResetMouseWheelOffset()
{
    mMouseWheelOffset = glm::vec2(0);
}

glm::vec2 Example01::GetCurrentMousePosition()
{
    return mMousePosition;
}

// Static callback functions.
void Example01::OnGlfwSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Example01* exampleWindow = static_cast<Example01*>(glfwGetWindowUserPointer(window));
    exampleWindow->OnKeyInput(key, scancode, action, mods);
}

void Example01::OnGlfwSetCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    Example01* exampleWindow = static_cast<Example01*>(glfwGetWindowUserPointer(window));
    exampleWindow->OnMousePositionChanged(xpos, ypos);
}

void Example01::OnGlfwSetMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    Example01* exampleWindow = static_cast<Example01*>(glfwGetWindowUserPointer(window));
    exampleWindow->OnMouseButton(button, action, mods);
}

void Example01::OnGlfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Example01* exampleWindow = static_cast<Example01*>(glfwGetWindowUserPointer(window));
    exampleWindow->OnFramebufferSizeChanged(width, height);
}

void Example01::OnGlfwSetScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Example01* exampleWindow = static_cast<Example01*>(glfwGetWindowUserPointer(window));
    exampleWindow->OnMouseWheelChanged(xoffset, yoffset);
}

// Example callback member functions.
void Example01::OnFramebufferSizeChanged(int width, int height)
{
    glViewport(0, 0, width, height);
    mWindowParam.width = width;
    mWindowParam.height = height;
    //std::cout << "[OnFramebufferSizeChanged] " << width << ", " << height << std::endl;
}

void Example01::OnMousePositionChanged(double xpos, double ypos)
{
    //std::cout << "[OnMousePositionChanged] " << xpos << ", " << ypos << std::endl;
    mMousePosition.x = static_cast<float>(xpos);
    mMousePosition.y = static_cast<float>(ypos);
}

void Example01::OnMouseButton(int button, int action, int mods)
{
    //std::cout << "[OnMouseButton] " << button << ", " << action << ", " << mods << std::endl;
}

void Example01::OnMouseWheelChanged(double xoffset, double yoffset)
{
    //std::cout << "[OnMouseWheelChanged] " << xoffset << ", " << yoffset << std::endl;
    mMouseWheelOffset.x = static_cast<float>(xoffset);
    mMouseWheelOffset.y = static_cast<float>(yoffset);
}

void Example01::OnKeyInput(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        mKeyState[key] = true;
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(mGlfwWindow, true);
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        mKeyState[key] = false;
    }
}