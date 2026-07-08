#pragma once
#ifndef INPUT_MANAGER_CLASS_H
#define INPUT_MANAGER_CLASS_H

#include <map>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include <vector>
#include <windows.h>

class Window;

class InputManager
{
private:

	// Almacena la posición del mouse en coordenadas de pantalla (x, y). tipo glm::vec2
	glm::vec2 mousePosition = { 0,0 };

	// Todas las teclas que se van a registrar
	std::vector<int> keysToTrack = { VK_SPACE, VK_CONTROL};

	// Contiene todas las teclas del teclado y su estado (presionado o no)
	std::map<int, bool> keysStates;
public:

	/**
	 * @brief Constructor de InputManager.
	 * @param window Recibe la instancia de la ventana. Tipo Window&
	 */
	InputManager(Window& window);

	/*
	* @brief se ejecuta en cada frame, util para actualizar ciertos valores (ej: Posicion del mouse)
	*/
	void update();

	/*
	* @brief Comprueba si una tecla esta presionada. Tipo bool
	*/
	bool isKeyPressed(int key) const;

	//GETTER

	/**
	 * @brief Obtiene la posicion del mouse. Tipo glm::vec2
	 */
	glm::vec2 getMousePosition() const { return mousePosition; }
};

#endif