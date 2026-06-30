#include "glad/glad.h"

#include "vbo.h"

VBO::VBO(const GLfloat* vertices, const GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	/**
	 * @brief Transfiere los datos de los vértices (geometría) de la RAM a la VRAM.
	 * * Este comando toma el array de vértices y lo carga en el VBO (Vertex Buffer Object)
	 * actualmente vinculado. Al usar GL_ARRAY_BUFFER, le informamos a la GPU que esta
	 * memoria contendrá atributos de vértice (posiciones, texturas, normales, etc.),
	 * los cuales serán procesados posteriormente por el Vertex Shader.
	 */
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() const
{
	glDeleteBuffers(1, &ID);
}