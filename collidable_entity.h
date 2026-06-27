#pragma once
#ifndef COLLIDABLE_ENTITY_CLASS_H
#define COLLIDABLE_ENTITY_CLASS_H

#include <glad/glad.h>
#include <memory>

#include "entity.h"
#include "collision_box.h"
#include "collision_manager.h"

// Tipos de colision disponibles
enum class CollisionType { CHARACTER, WALL, AREA };

/**
* @brief Entidad que posee una colision
*/
class CollidableEntity : public Entity {
protected:
    // Referencia al CollisionBox. Tipo CollisionBox
    std::shared_ptr<CollisionBox> collider;

    // Tipo de colision de esta entidad. Tipo CollisionType
    CollisionType collisionType;

    // Determina si la colision esta activa. Tipo Bool
    bool isCollisionEnabled = true;

    // El id de la capa en la cual se colisiona.
    int layer = 0;

    // Determina desde que direccion existe la colision, por defecto esta {0,0} que significa que todos los lados. Tipo glm::vec2
    glm::vec2 oneWayCollisionDirection = { 0,0 };

    // Tiempo restante de inmunidad
    float collisionCooldown = 0.0f;

    // 100ms de inmunidad tras colisionar
    const float COOLDOWN_DURATION = .1f;

    /*
    * @brief Constructor por defecto, asigna el CollisionType WALL por defecto
    */
    CollidableEntity() : collisionType(CollisionType::WALL) {}
public:
    /*
    * @brief Destructor de collidableEntity
    */
    virtual ~CollidableEntity() {
        try {
            auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());
            CollisionManager::getInstance().removeCollidableEntity(self);
        }
        catch (...) {
        }
    };

    //Factoria de puntero para collidableEntity
    template<typename T, typename... Args>
    static std::shared_ptr<T> create(Args&&... args) {
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        CollisionManager::getInstance().addCollidableEntity(
            std::static_pointer_cast<CollidableEntity>(ptr)
        );
        return ptr;
    }

    /*
    * @brief Constructor por parametros, permite a los hijos seleccionar su tipo de colision
    * @param _collisionType Define el tipo de colision de la entidad. Tipo CollisionType
    */
    CollidableEntity(const CollisionType _collisionType) : collisionType(_collisionType) {};

    /*
    * @brief Actualiza el collisionCooldown
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    */
    void updateCollisionCooldown (float deltaTime) {
        if (collisionCooldown > 0.0f) {
            collisionCooldown -= deltaTime;
        }
    }

    /*
    * @brief Determina si la entidad esta lista para colisionar. Tipo bool
    */
    bool canCollide() const {
        return collisionCooldown <= 0.0f;
    }

    /*
    * @brief Inicia el collisionCooldown
    */
    void startCollisionCooldown() {
        collisionCooldown = COOLDOWN_DURATION;
    }

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param normal El vector normal de la colision. Tipo glm::vec2
    * @param collisionRes Estructura de datos con informacion de la colision (vector normal de colision, interseccion e interaccion). tipo CollisionResult
    */
    virtual void onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const CollisionResult collisionRes) = 0;

    /*
    * @brief Permite el movimiento de la entindad.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    */
    void move(float deltaTime) override;

    //GETTER

    /**
    * @brief Obtiene el CollisionBox. Tipo std::shared_ptr<CollisionBox>
    */
    std::shared_ptr<CollisionBox> getCollider() const { return collider; };

    /**
    * @brief Obtiene el collisionType. Tipo CollisionType
    */
    CollisionType getCollisionType() const { return collisionType; };

    /**
    * @brief Obtiene si la colision esta activa. Tipo bool
    */
    bool getIsCollisionEnabled() const { return isCollisionEnabled; };

    /**
     * @brief Obtiene el id de la capa en la cual se colisiona. Tipo int
     */
    int getLayer() const { return layer; }

    /*
    * @brief Obtiene el oneWayCollisionDirection. Tipo glm::vec2
    */
    glm::vec2 getOneWayCollisionDirection() const { return oneWayCollisionDirection; };


    //SETTER

    /**
    * @brief Define si la colision esta activa
    */
    void setIsCollisionEnabled(bool _isCollisionEnabled) { isCollisionEnabled = _isCollisionEnabled; };

    /**
    * @brief Cambia el valor de la variable layer
    */
    void setLayer(int _layer) { layer = _layer; }

    /*
    * @brief Establece el oneWayCollisionDirection. Tipo glm::vec2
    */
    void setOneWayCollisionDirection(glm::vec2 _oneWayCollisionDirection) { oneWayCollisionDirection = _oneWayCollisionDirection; };
    
};
#endif
