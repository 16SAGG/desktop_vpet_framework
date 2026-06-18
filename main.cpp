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

	Texture texture("texture_2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(renderer.shader, "tex0", 0);

	Sprite sprite(
		texture,
		glm::vec2(0, 0),
		glm::vec2(160, 160),
		glm::ivec2(0, 0),
		glm::vec2(1, 21),
		glm::vec2(16, 16),
		glm::vec2(1, 0)
	);

	float posX = 100.0f;
	float posY = 100.0f;
	float velocidad = 200.0f;

	proccess.run([&](float deltaTime) {
		//posX += velocidad * deltaTime;

		if (posX > 800.0f) posX = 0.0f;

		renderer.draw(sprite, window.projection);
		sprite.setPosition(glm::vec2(posX, posY));
	});

	glfwTerminate();
	return 0;
}