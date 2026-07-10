#include <glad/glad.h>
#include <stb/stb_image.h>

#include "texture.h"
#include "shader.h"

Texture::Texture(const char* image, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType) {
	this->type = texType;
	
	unsigned char* bytes = stbi_load(image, &this->widthImg, &this->heightImg, &this->numColCh, 0);

	glGenTextures(1, &this->ID);
	glActiveTexture(slot);
	glBindTexture(texType, this->ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, this->widthImg, this->heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(texType, 0);
}

void Texture::texUnit(const Shader& shader, const char* uniform, const GLuint unit)
{
	GLuint texUniID = glGetUniformLocation(shader.getID(), uniform);
	shader.activate();
	glUniform1i(texUniID, unit); 
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::unbind() const
{
	glBindTexture(type, 0);
}

void Texture::deleteTexture() const
{
	glDeleteTextures(1, &this->ID);
}