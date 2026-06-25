#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "renderer_2d.h"
#include "sprite.h"
#include "collision_box.h"
#include "character.h"
#include "window.h"
#include "process.h"
#include "collision_manager.h"
#include "borders_manager.h"
#include "windows_collidable_manager.h"

const glm::vec2 WINDOW_SIZE = { 800, 600 };

int main() {
	Window window(WINDOW_SIZE.x, WINDOW_SIZE.y);
	if (!window.window) return -1;

	Process process(window.window);

	Renderer2D renderer;

	auto collisionManager = std::make_shared<CollisionManager>();

	BordersManager bordersManager(WINDOW_SIZE, collisionManager, -70, 10, 10, 10);

	WindowsCollidableManager windowsCollidableManager;

	auto textureShared = std::make_shared<Texture>("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textureShared->texUnit(renderer.shader, "tex0", 0);
	auto spr1 = std::make_shared<Sprite>(textureShared);
	spr1->setSize({ 100, 100 });
	auto col1 = std::make_shared<CollisionBox>();
	col1->setSize({ 100,100 });
	auto char1 = std::make_shared<Character>(spr1, col1);
	char1->setPosition({ 200, 400 });
	char1->setAcceleration({ 0, 1});
	collisionManager -> addCollidableEntity(char1);

	auto spr2 = Sprite::createFromPath("texture_2.png", renderer);
	spr2 -> setFrameSize({ 16,16 });
	spr2 -> setFrameOffset({ 1, 21 });
	spr2 -> setFrameGap({ 1, 0 });
	spr2->setSize({ 100, 100 });
	auto col2 = std::make_shared<CollisionBox>();
	col2->setSize({ 100,100 });
	auto char2 = std::make_shared<Character>(spr2, col2);
	char2->setPosition({ 400, 400 });
	char2->setAcceleration({ -1, -1 });
	collisionManager->addCollidableEntity(char2);

	static int frameCounter = 0;
	process.run([&](float deltaTime) {
		collisionManager->update(deltaTime);

		char1->move(deltaTime);
		//char2->move(deltaTime);

		renderer.draw(spr1, window.projection);
		renderer.draw(spr2, window.projection);

		if (frameCounter++ % 60 == 0) {
			windowsCollidableManager.syncWindows(collisionManager); //Continuar probando con esto
		}

		for (const auto& activeWindow : windowsCollidableManager.getActiveWindows()) {
			renderer.drawColoredEntity(activeWindow -> getCollider(), window.projection, {1.0f, 0.0f, 0.0f, .5f});
			// Por alguna razon lo que se dibuja no esta teniendo contacto alguno
		}
		renderer.drawColoredEntity(char1->getCollider() , window.projection, { 1.0f, 0.0f, 0.0f, .5f });
	});

	glfwTerminate();
	return 0;
}