#pragma once
#ifndef WINDOWS_COLLIDABLE_MANAGER_CLASS_H
#define WINDOWS_COLLIDABLE_MANAGER_CLASS_H

#include <Windows.h>
#include <memory>
#include <vector>

class Wall;
class WindowCollidable;

/**
* @brief Crea y gestiona las ventanas con colision
*/
class WindowsCollidableManager
{
private:
    // Lista de todas las ventanas colisionables activas. Tipo std::vector<std::shared_ptr<WindowCollidable>>
    std::vector<std::shared_ptr<WindowCollidable>> activeWindows;
public:
    /*
    * @brief Constructor de WindowsCollidableManager
    */
    WindowsCollidableManager() {}
    
    /*
    * @brief Sincroniza todas las ventanas activas del SO al motor fisicas del juego
    */
    void syncWindows();

    /*
    * @brief Elimina todas las colisiones vinculadas a ventanas inactivas
    */
    void cleanupInactiveWindows();

    /*
    * @brief Actualiza las propiedades de las ventanas colisionables activas
    */
    void updateAllVisibleWindows();

    /*
    * @brief Incluye o actualiza las propiedades de una ventana colisionable.
    * @param hwnd Es la referencia a la ventana. Tipo HWND
    */
    void addOrUpdateWindow(HWND hwnd);

    //GETTER

    /*
    * @brief Obtiene las ventanas activas. Tipo std::vector<std::shared_ptr<WindowCollidable>>
    */
    std::vector<std::shared_ptr<WindowCollidable>>& getActiveWindows() { return activeWindows; };

};
#endif