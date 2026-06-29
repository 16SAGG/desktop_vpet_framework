#include "process.h"
#include "entity_manager.h"
#include "window.h"
#include "windows_collidable_manager.h"

const float MAX_DELTA_TIME = 0.1f;

Process::Process(Window& window) : window(window), lastFrame(0.0f) {}

void Process::run(const UpdateCallback updateFunc) {
    WindowsCollidableManager windowsCollidableManager;
    
    static int frameCounter = 0;
    while (!glfwWindowShouldClose(window.window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (deltaTime > MAX_DELTA_TIME) deltaTime = MAX_DELTA_TIME;
        glClear(GL_COLOR_BUFFER_BIT);

        EntityManager::getInstance().update(deltaTime, window);
        if (frameCounter++ % 60 == 0) {
            windowsCollidableManager.syncWindows();
        }
        if (updateFunc) {
            updateFunc(deltaTime);
        }

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }
}