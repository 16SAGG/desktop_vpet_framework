#pragma once
#ifndef COLLIDABLE_ENTITY_CLASS_H
#define COLLIDABLE_ENTITY_CLASS_H

#include <glad/glad.h>
#include <memory>

#include "entity.h"
#include "collision_box.h"

// Tipos de colision disponibles
enum class CollisionType { CHARACTER, WALL, AREA };

/*
Contiene datos de la colision.
*/
struct CollisionResult {
    bool intersecting; // Si intersecta o no.
    glm::vec2 normal; // Dirección del choque (ej: {0, -1} para un choque desde arriba)
    float penetration; // Cuántos píxeles se solapan
};

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
    CollidableEntity(const CollisionType _collisionType) : collisionType(_collisionType) {};

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param normal El vector normal de la colision. Tipo glm::vec2
    * @param collisionRes Estructura de datos con informacion de la colision (vector normal de colision, interseccion e interaccion). tipo CollisionResult
    */
    virtual void onCollision(const std::shared_ptr<CollidableEntity> other, const glm::vec2 normal, const CollisionResult collisionRes) = 0;


    /**
     * @brief Determina si este CollisionBox colisiona con otro o no. Tipo CollisionResult
    * @param otherEntity La entidad con la que colisiona. Tipo CollidableEntity
     * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
     */
    CollisionResult checkCollision(const std::shared_ptr<CollidableEntity> otherEntity, const float deltaTime);

    /*
    * @brief Comprueba si hay una colision especial de una direccion. Tipo bool
    * @param collisionDir Determina la direccion de la collision. Tipo CollidableEntity
    * @param collisionRes Estructura de datos de la colision (si intersecta, su vector normal y su penetracion).tipo CollisionResult
    */
    bool checkOneWayCollision(const glm::vec2 collisionDir, const CollisionResult collisionRes) const;

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
