#pragma once
#ifndef DESKTOP_PET_CLASS_H
#define DESKTOP_PET_CLASS_H

#include <memory>
#include "glm/fwd.hpp"

#include "character.h"

class Sprite;
class CollisionBox;
class Window;

/**
* @brief Clase de mascota de escritorio
*/
class DesktopPet : public Character
{
private:

	// Determina la friccion que se aplicara a la aceleracion. Tipo glm::vec2
	glm::vec2 friction = { 0, 0 };

	// Posicion del mouse. Tipo glm::vec2
	glm::vec2 mousePosition = { 0, 0 };
public:

	/**
	 * @brief Constructor de DesktopPet
	 */
	DesktopPet(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
	Character(_sprite, _collider)
	{};

	/*
	* @brief Aplica la friccion a la aceleracion, reduciendo su aceleracion en cada frame.
	* @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
	*/
	void applyFriction(const float deltaTime);

	/*
	* @brief Realiza un salto
	*/
	void jump();

	/*
	* @brief Actualiza el comportamiento de la entidad cada frame.
	* @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
	* @param window Referencia a la ventana que encapsula este objeto. Tipo Window
	*/
	void update(float deltaTime, Window& window) override;

	//SETTERS

	/*
	* @brief Establece la friccion que se aplicara a la aceleracion.
	*/
	void setFriction(const glm::vec2& _friction) { friction = _friction; };

	/*
	* @brief Establece la posicion del mouse.
	*/
	void setMousePosition(const glm::vec2& _mousePosition) { mousePosition = _mousePosition; };

	//GETTERS

	/**
	* @brief Obtiene la velocidad. Tipo glm::vec2
	*/
	glm::vec2 getVelocity() const override { 
		if (this->getIsGrounded()) {
			return (acceleration * direction * maxSpeed) + gravity;
		}
		else {
			return (acceleration * glm::vec2(direction.x, -1) * maxSpeed) + gravity;
		}
	}
};

#endif