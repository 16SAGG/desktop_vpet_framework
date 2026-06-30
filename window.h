#pragma once
#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/fwd.hpp"

/**
 * @brief Gestiona la ventana de la aplicacion
 */
class Window
{
public:
	// Referencia a la ventana
	GLFWwindow* window;
	// Proyección ortográfica 2D: convierte píxeles del mundo a coordenadas de clip.
	glm::mat4 projection;

	/**
	 * @brief Constructor de window.
	 * * @param width Ancho de la ventana. Tipo GLuint
	 * * @param height Alto de la ventana. Tipo GLuint
	 */
	Window(const GLuint width, const GLuint height);
};

#endif