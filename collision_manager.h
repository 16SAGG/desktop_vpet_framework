#pragma once
#ifndef COLLISION_MANAGER_CLASS_H
#define COLLISION_MANAGER_CLASS_H

#include "collidable_entity.h"
#include <algorithm>

/**
* @brief Es una caja empleada para detectar el contacto con otros
*/
class CollisionManager
{
private:
    // Contiene todas las entidades con colision que se que van a monitorear. Tipo std::vector<CollidableEntity*> 
    std::vector<std::shared_ptr<CollidableEntity>> collidableEntities;
public:
    /**
    * @brief Constructor de CollisionManager
    */
    CollisionManager() {};

    /**
    * @brief Monitor que consulta constantemente si hay colisiones
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. Tipo Float
    */
    void update(const float deltaTime);

    /*
    * @brief Incluye un nuevo CollidableEntity en el array a monitorear.
    * @params newCollidableEntity Es la entidad colisionable que se incluira. Tipo std::shared_ptr<CollidableEntity>
    */
    void addCollidableEntity(std::shared_ptr<CollidableEntity> newCollidableEntity);

    /*
    * @brief Remueve un CollidableEntity en el array a monitorear.
    * @params entityToRemove Es la entidad colisionable que se removera. Tipo std::shared_ptr<CollidableEntity>
    */
    void removeCollidableEntity(std::shared_ptr<CollidableEntity> entityToRemove);
};
#endif