
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/fwd.hpp"
#include <glm/gtc/matrix_transform.hpp>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>
#endif

#include "window.h"

#include <iostream>
Window :: Window() : window(nullptr), windowHWND(nullptr), projection(glm::mat4(1.0f)), screenWidth(0), screenHeight(0) {
	if (!glfwInit()) return;

	RECT workArea {};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

	screenWidth = workArea.right - workArea.left;
	screenHeight = workArea.bottom - workArea.top;

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	window = glfwCreateWindow(screenWidth, screenHeight, "Overlay", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	windowHWND = glfwGetWin32Window(window);
	#ifdef _WIN32
		LONG_PTR exStyle = GetWindowLongPtr(windowHWND, GWL_EXSTYLE);
		SetWindowLongPtr(windowHWND, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetLayeredWindowAttributes(windowHWND, 0, 255, LWA_ALPHA);
		SetWindowPos(windowHWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	projection = glm::ortho(0.0f, float(screenWidth), float(screenHeight), 0.0f, -1.0f, 1.0f);
}