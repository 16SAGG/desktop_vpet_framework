#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>

class VBO;

/**
 * @brief VAO (Vertex Array Object) es el "manual de instrucciones" que guarda cómo se deben leer los datos de cada VBO
 */
class VAO
{
private:
	// Identificador de VAO
	GLuint ID;
public:
	/**
	* @brief Constructor de VAO
	*/
	VAO();

	/**
	 * @brief Vincula un VBO al VAO actual y define el formato de los atributos de vértice.
	 * * Esta función establece el "Vertex Layout". Informa a OpenGL cómo desglosar los datos
	 * dentro del buffer de vértices (VBO), especificando qué secciones corresponden a
	 * posiciones, coordenadas de textura, colores, etc., para que el Vertex Shader pueda
	 * procesarlos correctamente.
	 * * @param VBO El buffer que contiene los datos de los vértices a configurar. Tipo VBO
	 * @param layout El índice del atributo en el Vertex Shader (ej. layout (location = 0)). Tipo GLuint
	 * @param numComponents Número de valores que componen este atributo (ej. 2 para vec2, 3 para vec3). Tipo GLuint
	 * @param type El tipo de dato (ej. GL_FLOAT). Tipo GLenum
	 * @param stride El tamaño en bytes de un bloque completo de datos (el "paso" entre vértices). Tipo GLsizeiptr
	 * @param offset El desplazamiento inicial (en bytes) dentro del bloque de datos. Tipo void*
	 */
	void linkAttrib(
		const VBO& VBO, 
		const GLuint layout, 
		const GLuint numComponents, 
		const GLenum type, 
		const GLsizeiptr stride, 
		const void* offset
	);
	/**
	 * @brief Activa el VAO
	 */
	void bind() const;
	/**
	 * @brief Desactiva el VAO
	 */
	void unbind() const;
	/**
	 * @brief Elimina el VAO
	 */
	void deleteVAO() const;

	//GETTERS

	/**
	 * @brief Obtiene el ID del VAO
	 */
	GLuint getID() const { return ID; };
};
#endif