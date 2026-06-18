#pragma once
#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>
#endif

class Window
{
public:
	GLFWwindow* window;
	glm::mat4 projection;

	Window(const GLuint width, const GLuint height);
};

#endif