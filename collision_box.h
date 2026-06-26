#pragma once
#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "entity.h"

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
};
#endif