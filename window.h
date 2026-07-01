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

	// Ancho de la ventana. Tipo GLuint
	GLuint screenWidth;

	// Ancho de la ventana. Tipo GLuint
	GLuint screenHeight;
public:

	/**
	 * @brief Constructor de window.
	 */
	Window();

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

	/**
	 * @brief Obtiene las dimensiones de la ventana. Tipo glm::vec2
	 */
	glm::vec2 getScreenSize() const { return {screenWidth, screenHeight}; }
};

#endif