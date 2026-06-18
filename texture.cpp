#include "texture.h"

/**
 * @brief Constructor: Carga un archivo de imagen y lo convierte en una textura de OpenGL.
 * * @param image Ruta del archivo (ej. "texture.png"). Tipo char*
 * @param texType El tipo de textura (usualmente GL_TEXTURE_2D). Tipo GLenum
 * @param slot La unidad de textura a usar (ej. GL_TEXTURE0, GL_TEXTURE1). Tipo GLenum
 * @param format El formato de color de los datos (ej. GL_RGBA, GL_RGB). Tipo GLenum
 * @param pixelType El tipo de dato de los canales de color (ej. GL_UNSIGNED_BYTE). Tipo GLenum
 */
Texture::Texture(const char* image, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType) {
	type = texType;
	
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(texType, 0);
}

/**
 * @brief Vincula una unidad de textura (slot) a una variable uniforme del shader.
 * * @param shader Objeto del shader que contiene la variable uniforme. Tipo Shader
 * @param uniform Nombre de la variable `uniform sampler2D` en el código GLSL. Tipo char*
 * @param unit El índice de la unidad de textura (0 para GL_TEXTURE0, 1 para GL_TEXTURE1, etc.). Tipo GLuint
 */
void Texture::texUnit(Shader& shader, const char* uniform, const GLuint unit)
{
	GLuint texUniID = glGetUniformLocation(shader.ID, uniform);
	shader.activate();
	glUniform1i(texUniID, unit); 
}

/**
 * @brief Activa la textura
 */
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

/**
 * @brief Desactiva la textura
 */
void Texture::unbind() const
{
	glBindTexture(type, 0);
}

/**
 * @brief Elimina la textura
 */
void Texture::deleteTexture() const
{
	glDeleteTextures(1, &ID);
}