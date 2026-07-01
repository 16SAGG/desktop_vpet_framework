#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "renderer_2d.h"
#include "window.h"
#include "process.h"
#include "borders_manager.h"
#include "entity_manager.h"
#include <memory>
#include "glm/fwd.hpp"

int main() {
	Window window;
	if (!window.getWindow()) return -1;

	Process process(window);

	BordersManager bordersManager(window.getScreenSize(), 0, 0, 0, 0);

	auto char1 = EntityManager::getInstance().createCharacter({
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
		.entityParams = {
			.position = { 200, 400 },
			.acceleration = { -1, -1 }
		}
	});

	std::shared_ptr<Texture> textureShared = std::make_shared<Texture>("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textureShared->texUnit(Renderer2D::getInstance().getShader(), "tex0", 0);

	auto char2 = EntityManager::getInstance().createCharacter({
		.sprite = EntityManager::getInstance().createSpriteTexture({
			.texture = textureShared,
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
		.entityParams = {
			.position = { 200, 600 },
			.acceleration = { -1, -1}
		}
	});

	process.run([&](float deltaTime) {
	});

	glfwTerminate();
	return 0;
}