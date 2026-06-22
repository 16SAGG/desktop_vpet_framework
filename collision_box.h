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
private:
	// El id de la capa en la cual se colisiona.
	int layer = 0;
public:
    /**
     * @brief Constructor del CollisionBox
     */
    CollisionBox() {};

    /**
     * @brief Determina si este CollisionBox colisiona con otro o no.
     * * @param other El CollisionBox con el que se comparara la interseccion. Tipo CollisionBox&
     */
    CollisionResult checkCollision(const std::shared_ptr<CollisionBox> other) const;

    // SETTERS

    /**
    * @brief Cambia el valor de la variable layer
    */
    void setLayer(int _layer) { layer = _layer; }

    // GETTERS

    /**
     * @brief Obtiene el id de la capa en la cual se colisiona. Tipo int
     */
    int getLayer() const { return layer; }
};
#endif