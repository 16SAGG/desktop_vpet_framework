#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "renderer_2d.h"
#include "sprite.h"
#include "window.h"
#include "proccess.h"

int main() {
	Window window(800, 600);
	if (!window.window) return -1;

	Proccess proccess(window.window);

	Renderer2D renderer;

	auto textureShared = std::make_shared<Texture>("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textureShared -> texUnit(renderer.shader, "tex0", 0);

	Sprite sprite(textureShared);

	Sprite sprite2 = Sprite::createFromPath("texture_2.png", renderer);
	sprite2.setSize({ 100, 100 });
	sprite2.setFrameSize({ 16,16 });
	sprite2.setFrameOffset({ 1, 21 });
	sprite2.setFrameGap({ 1, 0 });

	float posX = 100.0f;
	float posY = 100.0f;
	float velocidad = 200.0f;

	proccess.run([&](float deltaTime) {
		posX += velocidad * deltaTime;

		if (posX > 800.0f) posX = 0.0f;

		sprite.setPosition({ posX, posY });
		sprite2.setPosition({ posX, 300 });

		renderer.draw(sprite, window.projection);
		renderer.draw(sprite2, window.projection);
	});

	glfwTerminate();
	return 0;
}