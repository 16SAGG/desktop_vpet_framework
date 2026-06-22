#pragma once
#ifndef COLLIDABLE_ENTITY_CLASS_H
#define COLLIDABLE_ENTITY_CLASS_H

#include <glad/glad.h>
#include <memory>

#include "entity.h"
#include "collision_box.h"

/**
* @brief Entidad que posee una colision
*/
class CollidableEntity : public Entity {
protected:
    // Referencia al CollisionBox. Tipo CollisionBox
    std::shared_ptr<CollisionBox> collider;

public:
    virtual ~CollidableEntity() = default;

    /**
    * @brief Obtiene el CollisionBox. Tipo std::shared_ptr<CollisionBox>
    */
    std::shared_ptr<CollisionBox> getCollider() { return collider; }

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * * @params other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    */
    virtual void onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) = 0;
};
#endif
