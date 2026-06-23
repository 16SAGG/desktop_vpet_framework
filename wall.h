#pragma once
#ifndef WALL_CLASS_H
#define WALL_CLASS_H

#include <glad/glad.h>
#include <memory>

#include "collidable_entity.h"
#include "collision_box.h"

/**
* @brief Entidad con colision estatica
*/
class Wall : public CollidableEntity {
protected:
    // Determina desde que direccion existe la colision, por defecto esta {0,0} que significa que todos los lados. Tipo glm::vec2
    glm::vec2 oneWayCollisionDirection = { 0,0 };
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
     * * @params other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
     */
    void onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 normal, CollisionResult collisionRes) {};

    //GETTER

    /*
    * @brief Obtiene el oneWayCollisionDirection. Tipo glm::vec2
    */
    glm::vec2 getOneWayCollisionDirection() const { return oneWayCollisionDirection; };

    //SETTER

    /*
    * @brief Establece el oneWayCollisionDirection. Tipo glm::vec2
    */
    void setOneWayCollisionDirection(glm::vec2 _oneWayCollisionDirection) { oneWayCollisionDirection = _oneWayCollisionDirection; };

    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    void setChildrenPosition(const glm::vec2& _position) {
        collider->setPosition(_position);
    }
};
#endif
