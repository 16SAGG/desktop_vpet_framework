#pragma once
#ifndef BORDERS_MANAGER_CLASS_H
#define BORDERS_MANAGER_CLASS_H

#include <vector>
#include <memory>
#include <glm/fwd.hpp>

class Wall;

/**
* @brief Crea y gestiona la colision de los bordes de la ventana
*/
class BordersManager
{
private:
    // Lista de los borders para mantenerlos vivos.std::vector<std::shared_ptr<Wall>>
    std::vector<std::shared_ptr<Wall>> borders; 
public:
    /**
    * @brief Constructor de BordersManager
    * @param screenSize Es el tamano de la pantalla. Tipo glm::vec2 screenSize
    * @param collisionManager Gestor de colisiones al que se le incluiran las colisiones de los bordes. Tipo std::shared_ptr<CollisionManager>
    * @param topMargin Es el espacio que se agrega o resta a la posicion del borde superior. Tipo float
    * @param leftMargin Es el espacio que se agrega o resta a la posicion del borde izquierdo. Tipo float
    * @param rightMargin Es el espacio que se agrega o resta a la posicion del borde derecho. Tipo float
    * @param bottomMargin Es el espacio que se agrega o resta a la posicion del borde inferior. Tipo float
    */
    BordersManager(
        const glm::vec2 screenSize,
        const float topMargin = 0, 
        const float leftMargin = 0,
        const float rightMargin = 0,
        const float bottomMargin = 0
    );

    /*
    * @brief Crea un borde. Tipo std::shared_ptr<Wall>
    * @param size tamano de la colision. Tipo glm::vec2 size
    * @param position ubicacion de la colision. Tipo glm::vec2 size
    * @param oneWayDir direccion de la colision. Tipo glm::vec2 size
    */
    std::shared_ptr<Wall> createBorder(const glm::vec2 size, const glm::vec2 position, const glm::vec2 oneWayDir);
};
#endif