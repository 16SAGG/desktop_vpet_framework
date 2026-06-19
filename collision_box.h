#pragma once
#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "entity.h"

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
    bool intersects(const CollisionBox& other) const {
        if (getLayer() != other.getLayer()) return false;

        glm::vec2 min1 = getGlobalPosition();
        glm::vec2 max1 = min1 + getSize();

        glm::vec2 min2 = other.getGlobalPosition();;
        glm::vec2 max2 = min2 + other.getSize();

        return (min1.x < max2.x && max1.x > min2.x &&
            min1.y < max2.y && max1.y > min2.y);
    }

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