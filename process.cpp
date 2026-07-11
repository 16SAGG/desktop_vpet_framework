#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "process.h"
#include "entity_manager.h"
#include "window.h"
#include "windows_collidable_manager.h"
#include "renderer_2d.h"

const float MAX_DELTA_TIME = 0.1f;
const int SYNC_WINDOWS_EVERY_N_FRAMES = 60;

Process::Process(Window& window) : window(window), lastFrame(0.0f) {}

void Process::run(const UpdateCallback updateFunc) {
    WindowsCollidableManager windowsCollidableManager(this->window);
    
    static int frameCounter = 0;
    while (!glfwWindowShouldClose(this->window.getWindow())) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        if (deltaTime > MAX_DELTA_TIME) deltaTime = MAX_DELTA_TIME;
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        EntityManager::getInstance().update(deltaTime, this->window);
        
        if (frameCounter++ % SYNC_WINDOWS_EVERY_N_FRAMES == 0) {
            windowsCollidableManager.syncWindows();
        }
        for (const auto& rect : windowsCollidableManager.getWindowsCachedBorders()) {
            glm::vec2 pos = {
                static_cast<float>(rect.left),
                static_cast<float>(rect.top)
            };

            glm::vec2 size = {
                static_cast<float>(rect.right - rect.left),
                static_cast<float>(rect.bottom - rect.top)
            };

            Renderer2D::getInstance().drawBorder(pos, size, window.getProjection(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        }

        if (updateFunc) {
            updateFunc(deltaTime);
        }

        glfwSwapBuffers(this->window.getWindow());
        glfwPollEvents();
    }
}