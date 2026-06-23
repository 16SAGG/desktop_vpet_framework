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

const glm::vec2 WINDOW_SIZE = { 800, 600 };

int main() {
	Window window(WINDOW_SIZE.x, WINDOW_SIZE.y);
	if (!window.window) return -1;

	Process process(window.window);

	Renderer2D renderer;

	auto collisionManager = std::make_shared<CollisionManager>();

	BordersManager bordersManager(WINDOW_SIZE, collisionManager, 10.0);

	auto textureShared = std::make_shared<Texture>("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textureShared -> texUnit(renderer.shader, "tex0", 0);
	auto spr1 = std::make_shared<Sprite>(textureShared);
	spr1->setSize({ 100, 100 });
	auto col1 = std::make_shared<CollisionBox>();
	col1 -> setSize({100,100});
	auto char1 = std::make_shared<Character>(spr1, col1);
	char1->setPosition({ 400, -200 });
	char1->setAcceleration({ 1, 1});
	collisionManager -> addCollidableEntity(char1);

	auto spr2 = Sprite::createFromPath("texture_2.png", renderer);
	spr2 -> setFrameSize({ 16,16 });
	spr2 -> setFrameOffset({ 1, 21 });
	spr2 -> setFrameGap({ 1, 0 });
	spr2->setSize({ 100, 100 });
	auto col2 = std::make_shared<CollisionBox>();
	col2->setSize({ 100,100 });
	auto char2 = std::make_shared<Character>(spr2, col2);
	char2->setPosition({ 400, 800 });
	char2->setAcceleration({ -1, -1 });
	collisionManager->addCollidableEntity(char2);

	process.run([&](float deltaTime) {
		char1->move(deltaTime);
		char2->move(deltaTime);

		renderer.draw(spr1, window.projection);
		renderer.draw(spr2, window.projection);
		collisionManager->update();
	});

	glfwTerminate();
	return 0;
}