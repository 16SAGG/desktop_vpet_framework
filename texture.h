#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader_class.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;

	int widthImg, heightImg, numColCh;

	Texture(const char* image, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void bind() const;
	void unbind() const;
	void deleteTexture() const;
};
#endif