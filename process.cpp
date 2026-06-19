#include "process.h"

const float MAX_DELTA_TIME = 0.1f;

Process::Process(GLFWwindow* window) : window(window), lastFrame(0.0f) {}

void Process::run(const UpdateCallback updateFunc) {
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (deltaTime > MAX_DELTA_TIME) deltaTime = MAX_DELTA_TIME;
        glClear(GL_COLOR_BUFFER_BIT);

        if (updateFunc) {
            updateFunc(deltaTime);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}