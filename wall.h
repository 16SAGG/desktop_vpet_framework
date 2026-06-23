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
public:
    /*
    * @brief Constructor por defecto de la clase Wall
    * @param _collider Referencia al CollisionBox. Tipo CollisionBox
    */
    Wall(std::shared_ptr<CollisionBox> _collider) :
        CollidableEntity(CollisionType::CHARACTER)
    {
        this->collider = _collider;
    }

    /**
     * @brief Determina el comportamiento de esta entiendad a colisionar.
     * * @params other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
     */
    void onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) {};
};
#endif
