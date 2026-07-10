#include "glad/glad.h"

#include "vbo.h"

VBO::VBO(const GLfloat* vertices, const GLsizeiptr size)
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() const
{
	glDeleteBuffers(1, &this->ID);
}