#include "vao.h"

/**
 * @brief VAO (Vertex Array Object) es el "manual de instrucciones" que guarda cómo se deben leer los datos de cada VBO
 */

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

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

/**
 * @brief Activa el VAO
 */
void VAO::bind() const
{
	glBindVertexArray(ID);
}

/**
 * @brief Desactiva el VAO
 */
void VAO::unbind() const
{
	glBindVertexArray(0);
}

/**
 * @brief Elimina el VAO
 */
void VAO::deleteVAO() const
{
	glDeleteVertexArrays(1, &ID);
}