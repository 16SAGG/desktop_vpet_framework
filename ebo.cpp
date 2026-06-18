#include "ebo.h"

EBO::EBO(const GLuint* indices, const GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	/**
	 * Transfiere los datos de índices de la CPU a la VRAM de la GPU.
	 * Este comando reserva memoria en la tarjeta gráfica y carga el array de índices.
	 * Usamos GL_STATIC_DRAW como "hint" al driver para indicar que esta geometría
	 * es permanente (no cambia en tiempo de ejecución), optimizando su ubicación
	 * en la memoria de video más rápida.
	 */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteEBO() const
{
	glDeleteBuffers(1, &ID);
}