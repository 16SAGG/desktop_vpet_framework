#pragma once
#ifndef DESKTOP_PET_CLASS_H
#define DESKTOP_PET_CLASS_H

#include <memory>
#include <vector>
#include "glm/fwd.hpp"

#include "character.h"
#include "entity.h"

// Estructura que contiene la direccion y distancia hacia un objetivo
struct TargetData {
	glm::vec2 direction;
	glm::vec2 distance;
};

// Enum que define los diferentes comportamientos de movimiento de la mascota de escritorio
// FOLLOW_CURSOR: La mascota sigue la posición del cursor del mouse
// FOLLOW_TARGETS: La mascota sigue objetivos específicos de una lista
// WANDER: La mascota deambula aleatoriamente por la pantalla
enum MovementBehavior {
	FOLLOW_CURSOR,
	FOLLOW_TARGETS,
	WANDER
};

class Sprite;
class CollisionBox;
class Window;

/**
* @brief Clase de mascota de escritorio
*/
class DesktopPet : public Character
{
private:

	// Determina la friccion que se aplicara a la aceleracion en el aire. Tipo float
	float airFriction = 0.0f;

	// Determina si la tecla para activar el comportamiento FOLLOW_CURSOR esta presionada
	bool followCursorKeyIsPressed = false;

	// Posicion del mouse. Tipo glm::vec2
	glm::vec2 mousePosition = { 0, 0 };

	// Contiene todas las entidades que la mascota de escritorio seguira. std::vector<std::shared_ptr<Entity>> 
	std::vector<std::shared_ptr<Entity>> targetsToFollow;

	// Proxima posicion a la que se desplazara el personaje en su estado Wander. Tipo glm::vec2
	glm::vec2 wanderPosition = { 0,0 };

	// Contador de Frames a partir de cuando se empieza el desplazamiento en el estado Wander. int
	int wanderFrames = 0;
public:

	/**
	 * @brief Constructor de DesktopPet
	 */
	DesktopPet(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
	Character(_sprite, _collider)
	{};

	/*
	* @brief Permite el movimiento de la entindad.
	* @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
	*/
	void move(float deltaTime) override;

	/*
	* @brief Maneja el comportamiento en tierra
	* @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
	* @param distanceToTarget Distancia hacia el objetivo. Tipo glm::vec2
	*/
	void handleGroundMovement(float deltaTime, glm::vec2 distanceToTarget);

	/*
	* @brief Maneja el comportamiento aereo
	* @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
	*/
	void handleAirMovement(float deltaTime);

	/*
	* @brief Realiza un salto
	*/
	void jump();

	/*
	* @brief Incluye una nueva entidad para seguir
	* @params newTargetToFollow Es la entidad que se incluira. Tipo std::shared_ptr<Entity>
	*/
	void addTargetToFollow(const std::shared_ptr<Entity> newTargetToFollow);

	//SETTERS

	/*
	* @brief Establece la friccion que se aplicara a la aceleracion.
	*/
	void setAirFriction(const float _airFriction) { this->airFriction = _airFriction; };

	/*
	* @brief Establece si la tecla para activar el comportamiento FOLLOW_CURSOR esta presionada
	* @param _followCursorKeyIsPressed. Tipo bool
	*/
	void setFollowCursorKeyIsPressed(bool _followCursorKeyIsPressed) { this->followCursorKeyIsPressed = _followCursorKeyIsPressed; }

	/*
	* @brief Establece la posicion del mouse.
	*/
	void setMousePosition(const glm::vec2& _mousePosition) { this->mousePosition = _mousePosition; };

	/*
	* @brief Establece la proxima posicion a la que se desplazara el personaje en su estado Wander. Tipo glm::vec2
	*/
	void setWanderPosition(const glm::vec2& _wanderPosition);

	//GETTERS

	/*
	* @brief Obtiene el comportamiento del personaje al moverse
	*/
	MovementBehavior getCurrentMovementBehavior();

	/*
	* @brief Obtiene la direccion y distancia hacia el objetivo. Tipo TargetData
	* @param targetPosition Posicion del objetivo. Tipo glm::vec2
	*/
	TargetData getTargetData(glm::vec2 targetPosition) const;

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