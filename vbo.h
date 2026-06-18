#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID;

	VBO(const GLfloat* vertices, const GLsizeiptr size);

	void bind() const;
	void unbind() const;
	void deleteVBO() const;
};

#endif