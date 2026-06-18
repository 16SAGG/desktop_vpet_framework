#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

/**
* @brief EBO (Element Buffer Object) es el "almacén" donde guardaremos los índices que definen
* cómo se deben dibujar los vértices. Es util para reutilizar vértices y evitar duplicados,
* lo que puede mejorar el rendimiento del renderizado.
*/
class EBO
{
private:
	//Identificador del EBO
	GLuint ID;
public:
	/**
	 * @brief Constructor de EBO
	 * * @param indices Matriz de indices. Tipo GLuint
	 * @param size Tamaño de la matriz de indices. Tipo GLsizeiptr
	 */
	EBO(const GLuint* indices, const GLsizeiptr size);

	/**
	 * @brief Activa el EBO
	 */
	void bind() const;
	/**
	 * @brief Desactiva el EBO
	 */
	void unbind() const;
	/**
	 * @brief Elimina el EBO
	 */
	void deleteEBO() const;
};

#endif