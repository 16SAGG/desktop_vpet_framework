#pragma once
#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include <memory>
#include "glm/fwd.hpp"

#include "collidable_entity.h"

class Sprite;
class CollisionBox;
class Window;
class CollisionResult;

/**
* @brief Es una entidad colisionable con fisicas especializadas en movimiento y la gravedad.
*/
class Character : public CollidableEntity
{
protected:

    // Referencia al sprite del character. Tipo Sprite
    std::shared_ptr<Sprite> sprite;

	// Fuerza de gravedad que se aplica a este character. Tipo glm::vec2
	glm::vec2 gravity = { 0, 0 };

	// Determina si el character esta en el suelo. Tipo bool
	bool isGrounded = false;
public:

    /**
    * @brief Constructor de Character
    ** @param _sprite Referencia al sprite del character. Tipo Sprite
    * @param _collider Referencia al CollisionBox. Tipo CollisionBox
    */
    Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider); 

    /*
    * @brief Actualiza el comportamiento de la entidad cada frame.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    * @param window Referencia a la ventana que encapsula este objeto. Tipo Window
    */
    void update(float deltaTime, Window& window) override;

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param collisionNormalized La direccion de la colision. Tipo glm::vec2
    * @param penetration Determina cuanto fue la penetracion entre los dos objetos al colisionar. Tipo float
    */
    void onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) override;

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es detener el desplazamiento en la direccion a la que colisiona.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void stopUponImpact(const CollidableEntity* other, glm::vec2 normal);

    // GETTERS

    /*
    * @brief Obtinene una referencia al sprite. Tipo std::shared_ptr<Sprite>
    */
    std::shared_ptr<Sprite> getSprite() { return sprite; };

    /*
	* @brief Obtiene la fuerza de gravedad que se aplica a este character. Tipo glm::vec2
    */
	glm::vec2 getGravity() const { return gravity; };

    /*
	* @brief Obtiene el vector normal de la gravedad. Tipo glm::vec2
    */
	glm::vec2 getGravityNormalized() const { return glm::normalize(gravity); };

    /*
	* @brief Obtiene si el character esta en el suelo. Tipo bool
    */
	bool getIsGrounded() const { return isGrounded; };

    /**
    * @brief Obtiene la velocidad. Tipo glm::vec2
    */
    glm::vec2 getVelocity() const override { return (acceleration * direction * maxSpeed) + gravity; }

    // SETTERS
    
    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    void setChildrenPosition(const glm::vec2& _position);

    /*
	* @brief Cambia el valor de la variable gravity.
    */
	void setGravity(const glm::vec2& _gravity) { gravity = _gravity; };
};
#endif