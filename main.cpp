#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <Windows.h>
#include <iostream>

#include "window.h"
#include "process.h"
#include "borders_manager.h"
#include "entity_manager.h"
#include "input_manager.h"
#include "utils.h"
#include "desktop_pet.h"

int main() {
	Window window;
	if (!window.getWindow()) return -1;

	Process process(window);

	BordersManager bordersManager(Utils::getInstance().getScreenSize(), 0, 0, 0, 0);

	InputManager inputManager(window);

	auto pet1 = EntityManager::getInstance().createDesktopPet({
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
			.gravity = { 0, 1.0f },
			.entityParams = {
				.position = { 200, 400 },
				.maxSpeed = { 300, 600 }
			}
		},
		.jumpFramesDuration = 1200
	});

	auto char1 = EntityManager::getInstance().createCharacter({
		.sprite = EntityManager::getInstance().createSpritePath({
			.path = "texture.png",
			.spriteParams = {
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
		.gravity = { 0, 1.0f },
		.entityParams = {
			.position = { 500, 400 },
			.direction = { 0, 1 },
			.maxSpeed = { 300, 600 },
		}
	});

	process.run([&](float deltaTime) {
		inputManager.update();

		pet1->setMousePosition(inputManager.getMousePosition());
		pet1->setFollowCursorKeyIsPressed(inputManager.isKeyPressed(VK_CONTROL));
		pet1->setIsStopped(inputManager.isKeyPressed(VK_SPACE));
	});

	glfwTerminate();
	return 0;
}