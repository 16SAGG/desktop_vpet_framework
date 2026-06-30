#include "glad/glad.h"

#include "vao.h"
#include "vbo.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(
	const VBO& VBO, 
	const GLuint layout, 
	const GLuint numComponents, 
	const GLenum type, 
	const GLsizeiptr stride, 
	const void* offset
)
{
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind() const
{
	glBindVertexArray(ID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::deleteVAO() const
{
	glDeleteVertexArrays(1, &ID);
}