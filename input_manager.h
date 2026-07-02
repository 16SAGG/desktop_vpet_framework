#pragma once
#ifndef INPUT_MANAGER_CLASS_H
#define INPUT_MANAGER_CLASS_H

#include "glm/fwd.hpp"
#include <glm/glm.hpp>

class Window;

class InputManager
{
private:
	// Referencia a la ventana que encapsula este objeto.
	Window& window;

	// Almacena la posición del mouse en coordenadas de pantalla (x, y). tipo glm::vec2
	glm::vec2 mousePosition;
public:

	/**
	 * @brief Constructor de InputManager.
	 */
	InputManager(Window& window);

	//GETTER

	/**
	 * @brief Obtiene la posicion del mouse. Tipo glm::vec2
	 */
	glm::vec2 getMousePosition() const { return mousePosition; }

	void update();
};

#endif