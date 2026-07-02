#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "Windows.h"

#include <iostream>


#include "input_manager.h"
#include "window.h"

InputManager::InputManager(Window& _window) : window(_window), mousePosition({ 0,0 }) {
	if (!glfwInit()) return;
}

void InputManager::update() {
    POINT p;
    if (GetCursorPos(&p)) {
        mousePosition = {p.x, p.y};
    }
}