
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

Window :: Window(const GLuint width, const GLuint height) : window(nullptr), windowHWND(nullptr), projection(glm::mat4(1.0f)) {
	if (!glfwInit()) return;

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "Overlay", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	windowHWND = glfwGetWin32Window(window);
	#ifdef _WIN32
		LONG exStyle = GetWindowLong(windowHWND, GWL_EXSTYLE);
		SetWindowLong(windowHWND, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetWindowPos(windowHWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	projection = glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 1.0f);
}