#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool ShouldClose() const;
	void SwapBuffers();
	void PollEvents();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	GLFWwindow* GetWindow() const { return window; }
private:
	GLFWwindow* window;
	int width;
	int height;
	std::string title;

	void Init();
	static void ErrorCallback(int error, const char* description);
};

