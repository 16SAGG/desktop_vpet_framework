#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>

class Shader;

/**
* @brief Carga un archivo de imagen y lo convierte en una textura de OpenGL.
*/
class Texture
{
private:
	// Identificador de textura
	GLuint ID;
	// Tipo de la textura
	GLenum type;

	// Ancho de imagen
	int widthImg;
	// Alto de imagen
	int heightImg;
	// Numero del canal de color
	int numColCh;
public:
	/**
	 * @brief Constructor de texture
	 * * @param image Ruta del archivo (ej. "texture.png"). Tipo char*
	 * @param texType El tipo de textura (usualmente GL_TEXTURE_2D). Tipo GLenum
	 * @param slot La unidad de textura a usar (ej. GL_TEXTURE0, GL_TEXTURE1). Tipo GLenum
	 * @param format El formato de color de los datos (ej. GL_RGBA, GL_RGB). Tipo GLenum
	 * @param pixelType El tipo de dato de los canales de color (ej. GL_UNSIGNED_BYTE). Tipo GLenum
	 */
	Texture(const char* image, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType);

	/**
	 * @brief Vincula una unidad de textura (slot) a una variable uniforme del shader.
	 * * @param shader Objeto del shader que contiene la variable uniforme. Tipo Shader
	 * @param uniform Nombre de la variable `uniform sampler2D` en el código GLSL. Tipo char*
	 * @param unit El índice de la unidad de textura (0 para GL_TEXTURE0, 1 para GL_TEXTURE1, etc.). Tipo GLuint
	 */
	void texUnit(const Shader& shader, const char* uniform, GLuint unit);
	/**
	 * @brief Activa la textura
	 */
	void bind() const;
	/**
	 * @brief Desactiva la textura
	 */
	void unbind() const;
	/**
	 * @brief Elimina la textura
	 */
	void deleteTexture() const;

	//GETTERS

	/**
	 * @brief Obtiene el ancho de la imagen. Tipo int
	 */
	int getWidthImg() const { return widthImg; };
	/**
	 * @brief Obtiene el alto de la imagen. Tipo int
	 */
	int getHeightImg() const { return heightImg; };
};
#endif