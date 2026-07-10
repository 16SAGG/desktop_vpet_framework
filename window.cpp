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
#include "utils.h"

Window :: Window() : window(nullptr), windowHWND(nullptr), projection(glm::mat4(1.0f)) {
	if (!glfwInit()) return;

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	glm::vec2 screenSize = Utils::getInstance().getScreenSize();

	this->window = glfwCreateWindow(screenSize.x, screenSize.y, "Overlay", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	this->windowHWND = glfwGetWin32Window(this->window);
	#ifdef _WIN32
		LONG_PTR exStyle = GetWindowLongPtr(this->windowHWND, GWL_EXSTYLE);
		SetWindowLongPtr(this->windowHWND, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetLayeredWindowAttributes(this->windowHWND, 0, 255, LWA_ALPHA);
		SetWindowPos(this->windowHWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->projection = glm::ortho(0.0f, float(screenSize.x), float(screenSize.y), 0.0f, -1.0f, 1.0f);
}