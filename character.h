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
    * @param collisionRes Estructura con informacion de la colision (vector normal, interseccion e interaccion). Tipo CollisionResult
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    */
    void onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const CollisionResult collisionRes) override;

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es detener el desplazamiento en la direccion a la que colisiona.
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void stopUponImpact(const CollidableEntity* other, glm::vec2 normal);

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es rebotar.
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void bounce(const CollidableEntity* other, glm::vec2 normal);

    // SETTERS
    
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