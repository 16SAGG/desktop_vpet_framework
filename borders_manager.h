#pragma once
#ifndef BORDERS_MANAGER_CLASS_H
#define BORDERS_MANAGER_CLASS_H

#include "wall.h"
#include "collision_manager.h"
#include "collision_box.h"

/**
* @brief Crea y gestiona la colision de los bordes de la ventana
*/
class BordersManager
{
public:
    /**
    * @brief Constructor de BordersManager
    * @param screenSize Es el tamano de la pantalla. Tipo glm::vec2 screenSize
    * @param collisionManager Gestor de colisiones al que se le incluiran las colisiones de los bordes. Tipo std::shared_ptr<CollisionManager>
    * @param extraSpace Es el espacio adicional que se agrega al tamano de la pantalla. Tipo float
    */
    BordersManager(const glm::vec2 screenSize, const std::shared_ptr<CollisionManager> collisionManager, const float extraSpace = 0.0f);
};
#endif