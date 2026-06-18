#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>

#include"VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void linkAttrib(
		const VBO& VBO, 
		const GLuint layout, 
		const GLuint numComponents, 
		const GLenum type, 
		const GLsizeiptr stride, 
		const void* offset
	);
	void bind() const;
	void unbind() const;
	void deleteVAO() const;
};
#endif