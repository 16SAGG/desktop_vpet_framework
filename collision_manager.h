#pragma once
#ifndef COLLISION_MANAGER_CLASS_H
#define COLLISION_MANAGER_CLASS_H

#include "collidable_entity.h"

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
    */
    void update();

    /*
    * @brief Incluye un nuevo CollidableEntity en el array a monitorear.
    * @params newCollidableEntity Es la entidad colisionable que se incluira. Tipo std::shared_ptr<CollidableEntity>
    */
    void addCollidableEntity(std::shared_ptr<CollidableEntity> newCollidableEntity) {
        collidableEntities.push_back(newCollidableEntity);
    }
};
#endif