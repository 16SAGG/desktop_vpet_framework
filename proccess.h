#pragma once
#ifndef PROCCESS_CLASS_H
#define PROCCESS_CLASS_H

#include <functional>
#include <GLFW/glfw3.h>

class Proccess
{
public:
	using UpdateCallback = std::function<void(float)>;
	
	Proccess(GLFWwindow* window);

	void run(UpdateCallback updateFunc);
private:
	GLFWwindow* window;
	float lastFrame;
};

#endif