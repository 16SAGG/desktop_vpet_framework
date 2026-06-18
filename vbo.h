#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

/**
 * @brief VBO(Vertex Buffer Object) es el "almacén" donde guardaremos los datos de los vértices
 */
class VBO
{
private:
	// Identificador del VBO
	GLuint ID;
public:
	/**
	 * @brief Constructor de VBO
	 * * @param Vertices Matriz de vertices. Tipo GLfloat
	 * @param size Tamaño de la matriz de vertices. Tipo GLsizeiptr
	 */
	VBO(const GLfloat* vertices, const GLsizeiptr size);

	/**
	 * @brief Activa el VBO
	 */
	void bind() const;
	/**
	 * @brief Desactiva el VBO
	 */
	void unbind() const;
	/**
	 * @brief Elimina el VBO
	 */
	void deleteVBO() const;
};

#endif