#pragma once
#ifndef WINDOWS_COLLIDABLE_MANAGER_CLASS_H
#define WINDOWS_COLLIDABLE_MANAGER_CLASS_H

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include "wall.h"
#include "collision_manager.h"
#include "window_collidable.h"

/**
* @brief Crea y gestiona las ventanas con colision
*/
class WindowsCollidableManager
{
private:
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

    void cleanupInactiveWindows();

    void updateAllVisibleWindows();

    void addOrUpdateWindow(HWND hwnd);

    //GETTER

    /*
    * @brief Obtiene las ventanas activas. Tipo std::vector<std::shared_ptr<WindowCollidable>>
    */
    std::vector<std::shared_ptr<WindowCollidable>>& getActiveWindows() { return activeWindows; };

};
#endif