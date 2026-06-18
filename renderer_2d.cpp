#include "renderer_2d.h"

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

/**
 * @brief Constructor: Inicializa el pipeline de renderizado 2D.
 * * Este proceso carga el programa de shaders y prepara el VAO, VBO y EBO
 * con los datos necesarios para dibujar un cuadrado texturizado.
 */
Renderer2D::Renderer2D() : shader("default.vert", "default.frag") {
	VAO VAO1;
	VAO_id = VAO1.ID;
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
#include <string>
#include <fstream>
#include <iostream>
/**
 * @brief Renderiza un objeto 2D con una textura y transformación específica.
 * * Utiliza matrices para posicionar y escalar el objeto en el mundo virtual,
 * y envía estos datos al shader para su procesamiento final.
 * * @param texture Objeto de textura que se aplicará sobre la geometría. Tipo Texture&
 * @param pos Vector 2D (x, y) que indica la posición del objeto en el mundo. Tipo glm::vec2
 * @param size Vector 2D (ancho, alto) que indica la escala o dimensiones del objeto. Tipo glm::vec2
 * @param projection Matriz 4x4 de proyección que define cómo se mapean las coordenadas
 * del mundo a la pantalla (útil para manejar la relación de aspecto). Tipo glm::mat4&
 */
void Renderer2D::draw(const Sprite& sprite, const glm::mat4& projection) const{
	shader.activate();
	sprite.texture.bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(sprite.position, 0.0f));
	model = glm::scale(model, glm::vec3(sprite.size, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform2f(glGetUniformLocation(shader.ID, "textureSize"), (float)sprite.texture.widthImg, (float)sprite.texture.heightImg);
	glUniform2fv(glGetUniformLocation(shader.ID, "uvOffset"), 1, glm::value_ptr(sprite.getUVOffset()));
	glUniform2fv(glGetUniformLocation(shader.ID, "frameSize"), 1, glm::value_ptr(sprite.frameSize));

	glBindVertexArray(VAO_id);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}