#pragma once

#include <map>
#include <string>

#include "glm/glm.hpp"

#include "WindowParam.h"

// forward declaration.
struct GLFWwindow;

class Example01
{
public:
	Example01();
	virtual ~Example01();
	void Run();
	virtual void Initialize();
	virtual void Render();
	virtual void CleanUp();
	void SetCursorVisible(bool visible);
	bool GetKeyState(int key);
	glm::vec2 GetMouseWheelOffset();
	void ResetMouseWheelOffset();
	glm::vec2 GetCurrentMousePosition();

protected:
	GLFWwindow* CreateWindow(int width, int height, std::string title);

	// 윈도우 이벤트를 받을 콜백 함수들.
	static void OnGlfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void OnGlfwSetCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void OnGlfwSetMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void OnGlfwSetScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void OnGlfwSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	virtual void OnFramebufferSizeChanged(int width, int height);
	virtual void OnMousePositionChanged(double xpos, double ypos);
	virtual void OnMouseButton(int button, int action, int mods);
	virtual void OnMouseWheelChanged(double xoffset, double yoffset);
	virtual void OnKeyInput(int key, int scancode, int action, int mods);

protected:
	WindowParam mWindowParam{};
	GLFWwindow* mGlfwWindow{};
	std::string mTitle{};

	float mDeltaTime{};
	float mPrevTime{};

	std::map<int, bool> mKeyState{};
	glm::vec2 mMousePosition{};
	glm::vec2 mMouseWheelOffset{};
};