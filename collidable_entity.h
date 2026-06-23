#pragma once
#ifndef COLLIDABLE_ENTITY_CLASS_H
#define COLLIDABLE_ENTITY_CLASS_H

#include <glad/glad.h>
#include <memory>

#include "entity.h"
#include "collision_box.h"

// Tipos de colision disponibles
enum class CollisionType { CHARACTER, WALL, AREA };

/**
* @brief Entidad que posee una colision
*/
class CollidableEntity : public Entity {
protected:
    // Referencia al CollisionBox. Tipo CollisionBox
    std::shared_ptr<CollisionBox> collider;

    // Tipo de colision de esta entidad. CollisionType
    CollisionType collisionType;
public:
    /*
    * @brief Destructor de collidableEntity
    */
    virtual ~CollidableEntity() = default;

    /*
    * @brief Constructor por defecto, asigna el CollisionType WALL por defecto
    */
    CollidableEntity() : collisionType(CollisionType::WALL) {}

    /*
    * @brief Constructor por parametros, permite a los hijos seleccionar su tipo de colision
    * @param _collisionType Define el tipo de colision de la entidad. Tipo CollisionType
    */
    CollidableEntity(CollisionType _collisionType) : collisionType(_collisionType) {};

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    */
    virtual void onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) = 0;

    //GETTER

    /**
    * @brief Obtiene el CollisionBox. Tipo std::shared_ptr<CollisionBox>
    */
    std::shared_ptr<CollisionBox> getCollider() const { return collider; };

    /**
    * @brief Obtiene el collisionType. Tipo CollisionType
    */
    CollisionType getCollisionType() const { return collisionType; };
};
#endif
