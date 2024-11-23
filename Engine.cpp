#include <iostream>
#include "Window.h"

int main()
{
	Window window(800, 600, "Engine");

	while(!window.ShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render here

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;}
