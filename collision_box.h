#pragma once
#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include <memory>

#include "entity.h"

/*
Contiene datos de la colision. 
*/
struct CollisionResult {
    bool intersecting; // Si intersecta o no.
    glm::vec2 normal; // Dirección del choque (ej: {0, -1} para un choque desde arriba)
    float penetration; // Cuántos píxeles se solapan
};

/**
* @brief Es una caja empleada para detectar el contacto con otros
*/
class CollisionBox : public Entity
{
public:
    /**
     * @brief Constructor del CollisionBox
     */
    CollisionBox() {};

    /**
     * @brief Determina si este CollisionBox colisiona con otro o no.
     * * @param other El CollisionBox con el que se comparara la interseccion. Tipo CollisionBox&
     * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
     */
    CollisionResult checkCollision(const std::shared_ptr<CollisionBox> other, const float deltaTime);

};
#endif