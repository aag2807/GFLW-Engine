#pragma once

#include <GLFW/glfw3.h>
#include <array>
#include <unordered_map>


class Window;

class Input
{
public:
	explicit Input(Window& window);
	~Input() = default;

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	bool IsKeyPressed(int key) const;
	bool IsKeyHeld(int key) const;
	bool IsKeyReleased(int key) const;

	bool IsMouseButtonPressed(int button) const;
	void GetMousePosition(double& x, double& y) const;
	void GetCursorDelta(double& x, double& y);

	void Update();


private:
	struct KeyState {
		bool pressed = false;
		bool held = false;
		bool released = false;
	};

	Window& window;
	std::unordered_map<int, KeyState> keyStates;
	std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtons{};
	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
	double currentMouseX = 0.0;
	double currentMouseY = 0.0;
	bool firstMouse = true;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

	static Input* GetInput(GLFWwindow* window);
};

