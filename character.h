#pragma once
#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include "collidable_entity.h"
#include "sprite.h"
#include "wall.h"

/**
* @brief Es una caja empleada para detectar el contacto con otros
*/
class Character : public CollidableEntity
{
private:
    // Referencia al sprite del character. Tipo Sprite
    std::shared_ptr<Sprite> sprite;

    // Determina la velocidad de desplazamiento actual del personaje. Tipo glm::vec2
    glm::vec2 velocity = { 0, 0 };

    // Es la velocidad maxima del personaje. Tipo glm::vec2
    glm::vec2 maxSpeed = { 200, 200 };

    // Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    glm::vec2 acceleration = { 1, 0 };
public:
    /**
    * @brief Constructor de Character
    ** @param _sprite Referencia al sprite del character. Tipo Sprite
    * @param _collider Referencia al CollisionBox. Tipo CollisionBox
    */
    Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider); 

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param collisionNormalized La direccion de la colision. Tipo glm::vec2
    */
    void onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 collisionNormalized) override;

    /*
    * @brief Permite el movimiento del personaje.
    * @param deltaTime. tipo float.
    */
    void move(float deltaTime);

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es detener el desplazamiento en la direccion a la que colisiona.
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void stopUponImpact(glm::vec2 normal);

    // SETTERS
    
    /**
    * @brief Establecer la velocidad maxima.
    * * @param _acceleration Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    */
    void setSpeed(const glm::vec2& _maxSpeed) { maxSpeed = _maxSpeed; };

    /**
    * @brief Establecer acceleration.
    * * @param _acceleration Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    */
    void setAcceleration(const glm::vec2& _acceleration) { acceleration = _acceleration; };

    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    void setChildrenPosition(const glm::vec2& _position){
        sprite->setPosition(_position);
        collider->setPosition(_position);
    }
};
#endif