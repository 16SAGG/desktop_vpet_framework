#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "input_manager.h"
#include "window.h"

InputManager::InputManager(Window& window) {
    if (!glfwInit()) return;
}

void InputManager::update() {
    POINT p;
    if (GetCursorPos(&p)) {
        this->mousePosition = {p.x, p.y};
    }

    for (int key : keysToTrack) {
        this->keysStates[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
    }
}

bool InputManager::isKeyPressed(int key) const {
    auto it = this->keysStates.find(key);
    if (it != this->keysStates.end()) return it->second;
    return false;
}