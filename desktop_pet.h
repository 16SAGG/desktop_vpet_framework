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
	glm::vec2 targetPosition;
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
	STOP,
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

	// Determina si la tecla para activar el comportamiento FOLLOW_CURSOR esta presionada
	bool followCursorKeyIsPressed = false;

	// Posicion del mouse. Tipo glm::vec2
	glm::vec2 mousePosition = { 0, 0 };

	// Contiene todas las entidades que la mascota de escritorio seguira. std::vector<std::shared_ptr<Entity>> 
	std::vector<std::shared_ptr<Entity>> targetsToFollow;

	// Determina si el monstruo esta detenido
	bool isStopped = false;

	// Proxima posicion a la que se desplazara el personaje en su estado Wander. Tipo glm::vec2
	glm::vec2 wanderPosition = { 0,0 };

	// Contador de Frames a partir de cuando se empieza el desplazamiento en el estado Wander. Tipo int
	int wanderFrames = 0;

	// Determina si el monstruo esta saltando. Tipo int
	bool isJumping = false;

	// La informacion del objetivo hacia donde se salto. Tipo TargetData
	TargetData jumpTarget = {};

	// Contador de Frames a partir de que se inicializa el salto. Tipo int
	int jumpFrames = 0;

	// Cantidad maxima de frames de salto. Tipo int
	int	jumpFramesDuration = 0;
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
	* @brief Incluye una nueva entidad para seguir
	* @params newTargetToFollow Es la entidad que se incluira. Tipo std::shared_ptr<Entity>
	*/
	void addTargetToFollow(const std::shared_ptr<Entity> newTargetToFollow);

	//SETTERS

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
	* @brief Establece si el monstruo esta detenido o no
	*/
	void setIsStopped(const bool _isStopped) { this->isStopped = _isStopped; };

	/*
	* @brief Establece la proxima posicion a la que se desplazara el personaje en su estado Wander. Tipo glm::vec2
	*/
	void setWanderPosition(const glm::vec2& _wanderPosition);

	/*
	* @brief Establece la cantidad maxima en la duracion de salto
	* @param _jumpFramesDuration. Tipo int
	*/
	void setJumpFramesDuration(int _jumpFramesDuration) { jumpFramesDuration = _jumpFramesDuration; };

	//GETTERS

	//glm::vec2 getVelocity() const override { return acceleration * direction * maxSpeed; }

	/*
	* @brief Obtiene el comportamiento del personaje al moverse
	*/
	MovementBehavior getCurrentMovementBehavior();

	/*
	* @brief Obtiene la direccion y distancia hacia el objetivo. Tipo TargetData
	* @param targetPosition Posicion del objetivo. Tipo glm::vec2
	*/
	TargetData getTargetData(glm::vec2 targetPosition) const;
};

#endif