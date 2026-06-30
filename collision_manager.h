#pragma once
#ifndef COLLISION_MANAGER_CLASS_H
#define COLLISION_MANAGER_CLASS_H

#include <vector>
#include <memory>
#include "glm/fwd.hpp"

class CollidableEntity;

/*
Contiene datos de la colision.
*/
struct CollisionResult {
    bool intersecting; // Si intersecta o no.
    glm::vec2 normal; // Dirección del choque (ej: {0, -1} para un choque desde arriba)
    float penetration; // Cuántos píxeles se solapan
    CollidableEntity* otherEntity; // La entidad con la que se colisiona
};

/**
* @brief Es una caja empleada para detectar el contacto con otros
*/
class CollisionManager
{
private:
    // Contiene todas las entidades con colision que se que van a monitorear. Tipo std::vector<std::weak_ptr<CollidableEntity>> 
    std::vector<std::weak_ptr<CollidableEntity>> collidableEntities;

    /**
    * @brief Constructor de CollisionManager
    */
    CollisionManager() {};
public:
    /**
    * @brief Obtiene la unica instancia de CollisionManager
    */
    static CollisionManager& getInstance();

    /**
    * @brief Monitor que consulta si hay colisiones
    * @param originEntity La entidad que genera la colision. Tipo CollidableEntity
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. Tipo Float
    */
    CollisionResult checkCollision(const std::shared_ptr<CollidableEntity> originEntity, const float deltaTime) const;

    /**
     * @brief Determina si este CollisionBox colisiona con otro o no. Tipo CollisionResult
     * @param originEntity La entidad que genera la colision. Tipo CollidableEntity
     * @param otherEntity La entidad con la que colisiona. Tipo CollidableEntity
     * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
     */
    CollisionResult getCollision(const std::shared_ptr<CollidableEntity> originEntity, const std::shared_ptr<CollidableEntity> otherEntity, const float deltaTime) const;

    /*
    * @brief Comprueba si hay una colision especial de una direccion. Tipo bool
    * @param originEntity La entidad que genera la colision. Tipo CollidableEntity
    * @param collisionDir Determina la direccion de la collision. Tipo CollidableEntity
    * @param collisionRes Estructura de datos de la colision (si intersecta, su vector normal y su penetracion).tipo CollisionResult
    */
    bool getOneWayCollision(const std::shared_ptr<CollidableEntity> originEntity, const glm::vec2 collisionDir, const CollisionResult collisionRes) const;

    /*
    * @brief Incluye un nuevo CollidableEntity en el array a monitorear.
    * @params newCollidableEntity Es la entidad colisionable que se incluira. Tipo std::shared_ptr<CollidableEntity>
    */
    void addCollidableEntity(const std::shared_ptr<CollidableEntity> newCollidableEntity);

    /*
    * @brief Remueve un CollidableEntity en el array a monitorear.
    * @params entityToRemove Es la entidad colisionable que se removera. Tipo std::shared_ptr<CollidableEntity>
    */
    void removeCollidableEntity(const std::shared_ptr<CollidableEntity> entityToRemove);
};
#endif