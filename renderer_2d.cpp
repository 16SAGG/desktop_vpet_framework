#include "renderer_2d.h"
#include "sprite.h"

// POS_X, POS_Y, POS_Z,    COLOR_R, COLOR_G, COLOR_B,   TEX_U, TEX_V
const GLfloat VERTICES[] = {
	-0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f,            0.0f, 0.0f,
	-0.5f, 0.5f , 0.0f,        0.0f, 1.0f, 0.0f,            0.0f, 1.0f,
	0.5f ,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f,            1.0f, 1.0f,
	0.5f , -0.5f, 0.0f,        1.0f, 1.0f, 1.0f,            1.0f, 0.0f,
};

const GLuint INDICES[] = {
	0, 1, 2,
	0, 2, 3
};

Renderer2D::Renderer2D() : shader("default.vert", "default.frag") {
	VAO VAO1;
	VAO_id = VAO1.getID();
	VAO1.bind();

	VBO VBO1(VERTICES, sizeof(VERTICES));
	EBO EBO1(INDICES, sizeof(INDICES));

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();
}

void Renderer2D::draw(const Sprite& sprite, const glm::mat4& projection) const{
	shader.activate();
	sprite.getTexture() -> bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(sprite.getGlobalPosition(), 0.0f));
	model = glm::scale(model, glm::vec3(sprite.getSize(), 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform2f(glGetUniformLocation(shader.getID(), "textureSize"), (float)sprite.getTexture() -> getWidthImg(), (float)sprite.getTexture() -> getHeightImg());
	glUniform2fv(glGetUniformLocation(shader.getID(), "uvOffset"), 1, glm::value_ptr(sprite.getUVOffset()));
	glUniform2fv(glGetUniformLocation(shader.getID(), "frameSize"), 1, glm::value_ptr(sprite.getFrameSize()));

	glBindVertexArray(VAO_id);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}