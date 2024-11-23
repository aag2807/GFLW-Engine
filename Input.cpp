#include "Input.h"
#include "Window.h"

Input::Input(Window& window) : window(window)
{
	GLFWwindow* nativeWindow = window.GetWindow();

	glfwSetKeyCallback(nativeWindow, KeyCallback);
	glfwSetMouseButtonCallback(nativeWindow, MouseButtonCallback);
	glfwSetCursorPosCallback(nativeWindow, CursorPositionCallback);
}

void Input::Update()
{
	for (auto& pair : keyStates)
	{
		pair.second.pressed = false;
		pair.second.released = false;
	}

	if (firstMouse)
	{
		lastMouseX = currentMouseX;
		lastMouseY = currentMouseY;
		firstMouse = false;
	}
}

bool Input::IsKeyPressed(int keyCode) const
{
	auto it = keyStates.find(keyCode);
	return it != keyStates.end() && it->second.pressed;
}

bool Input::IsKeyHeld(int keyCode) const
{
	auto it = keyStates.find(keyCode);
	return it != keyStates.end() && it->second.held;
}

bool Input::IsKeyReleased(int keyCode) const
{
	auto it = keyStates.find(keyCode);
	return it != keyStates.end() && it->second.released;
}

bool Input::IsMouseButtonPressed(int button) const
{
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
	{
		return mouseButtons[button];
	}

	return false;
}

void Input::GetMousePosition(double& x, double& y) const
{
	x = currentMouseX;
	y = currentMouseY;
}

void Input::GetCursorDelta(double& dx, double& dy)
{
	dx = currentMouseX - lastMouseX;
	dy = currentMouseY - lastMouseY;
	lastMouseX = currentMouseX;
	lastMouseY = currentMouseY;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input* input = GetInput(window);
	if (!input)
	{
		return;
	}

	auto state = input->keyStates[key];

	switch (action)
	{
	case GLFW_PRESS:
		state.pressed = true;
		state.held = true;
		break;
	case GLFW_RELEASE:
		state.released = true;
		state.held = false;
		break;
	case GLFW_REPEAT:
		// TODO: Handle repeat
		break;
	default:
		break;
	}

}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Input* input = GetInput(window);
	if (!input || button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
	{
		return;
	}

	input->mouseButtons[button] = (action == GLFW_PRESS);
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input* input = GetInput(window);
	if (!input)
	{
		return;
	}

	input->currentMouseX = xpos;
	input->currentMouseY = ypos;
}

Input* Input::GetInput(GLFWwindow* window)
{
	return static_cast<Input*>(glfwGetWindowUserPointer(window));
}
