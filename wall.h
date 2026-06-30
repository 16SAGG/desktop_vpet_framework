#pragma once
#ifndef WALL_CLASS_H
#define WALL_CLASS_H

#include <memory>
#include "glm/fwd.hpp"

#include "collidable_entity.h"
#include "collision_box.h"

/**
* @brief Entidad con colision estatica
*/
class Wall : public CollidableEntity {
public:
    /*
    * @brief Constructor por defecto de la clase Wall
    * @param _collider Referencia al CollisionBox. Tipo CollisionBox
    */
    Wall(std::shared_ptr<CollisionBox> _collider) :
        CollidableEntity(CollisionType::WALL)
    {
        this->collider = _collider;
    }

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param collisionNormalized La direccion de la colision. Tipo glm::vec2
    * @param penetration Determina cuanto fue la penetracion entre los dos objetos al colisionar. Tipo float
    */
    void onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) {};

    //SETTER
    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    void setChildrenPosition(const glm::vec2& _position) {
        collider->setPosition(_position);
    }
};
#endif
