#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "texture.h"
#include "renderer_2d.h"
#include "window.h"
#include "process.h"
#include "borders_manager.h"
#include "entity_manager.h"
#include "input_manager.h"
#include "utils.h"
#include "desktop_pet.h"

#include "glm/fwd.hpp"

int main() {
	Window window;
	if (!window.getWindow()) return -1;

	Process process(window);

	BordersManager bordersManager(window.getScreenSize(), 0, 0, 0, 0);

	InputManager inputManager(window);

	auto pet1 = EntityManager::getInstance().createDesktopPet({
		.friction = { 0, .5f },
		.characterParams = {
			.sprite = EntityManager::getInstance().createSpritePath({
				.path = "texture_2.png",
				.spriteParams = {
					.frameSize = { 16, 16},
					.frameOffset = { 1, 21 },
					.frameGap = { 1, 0 },
					.entityParams = {
						.size = { 100, 100 }
					}
				}
			}),
			.collider = EntityManager::getInstance().createCollisionBox({
				.entityParams = {
					.size = { 100, 100 }
				}
			}),
			.gravity = { 0, 180.0f },
			.entityParams = {
				.position = { 200, 400 },
				.maxSpeed = { 300, 600 }
			}
		},
	});

	process.run([&](float deltaTime) {
		inputManager.update();

		pet1->setMousePosition(inputManager.getMousePosition());
	});

	glfwTerminate();
	return 0;
}