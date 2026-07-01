#pragma once
#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include <Windows.h>

/**
 * @brief Gestiona la ventana de la aplicacion
 */
class Window
{
private:
	// Referencia a la ventana de GLFW. Tipo GLFWwindow*
	GLFWwindow* window;

	// Referencia a la ventana del sistema operativo. Tipo HWND
	HWND windowHWND; 
	
	// Proyección ortográfica 2D: convierte píxeles del mundo a coordenadas de clip. Tipo glm::mat4
	glm::mat4 projection;
public:

	/**
	 * @brief Constructor de window.
	 * * @param width Ancho de la ventana. Tipo GLuint
	 * * @param height Alto de la ventana. Tipo GLuint
	 */
	Window(const GLuint width, const GLuint height);

	//GETTER
	
	/**
	 * @brief Obtiene la referencia a la ventana de GLFW. Tipo GLFWwindow*
	 */
	GLFWwindow* getWindow() const { return window; }

	/**
	 * @brief Obtiene la referencia a la ventana del sistema operativo. Tipo HWND
	 */
	HWND getWindowHWND() const { return windowHWND; }

	/**
	 * @brief Obtiene la Proyección ortográfica 2D. Tipo glm::mat4
	 */
	glm::mat4 getProjection() const { return projection; }
};

#endif