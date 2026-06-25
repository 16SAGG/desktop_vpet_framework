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
    void syncWindows(std::shared_ptr<CollisionManager> collisionManager) {
        //std::cout << activeWindows.size();
        //system("cls");

        struct CallbackData {
            WindowsCollidableManager* self;
            std::shared_ptr<CollisionManager> _collisionManager;
        };

        CallbackData data = { this, collisionManager };
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            auto data = reinterpret_cast<CallbackData*>(lParam);

            //if (hwnd == data->gameWindowHandle) return TRUE;

            // 1. DWM Cloak: Elimina minimizadas y ventanas en segundo plano
            int cloaked = 0;
            if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked != 0)
                return TRUE;

            // 2. Filtro de Estilo: Ignora ventanas que no tienen bordes de aplicación normal
            // WS_POPUP y WS_CAPTION son necesarios para ventanas interactivas normales
            LONG style = GetWindowLong(hwnd, GWL_STYLE);
            if (!(style & WS_VISIBLE)) return TRUE; // Si no es visible, descartar

            // 3. Obtener el estado real de la ventana
            WINDOWPLACEMENT wp;
            wp.length = sizeof(WINDOWPLACEMENT);
            GetWindowPlacement(hwnd, &wp);

            // Si está minimizada (la ventana tiene un estado de "minimizada" en el sistema)
            if (wp.showCmd == SW_SHOWMINIMIZED) return TRUE;

            // 4. Excluir las "fantasma" que tienen tamaño 0x0
            RECT rect;
            GetWindowRect(hwnd, &rect);
            if ((rect.right - rect.left) <= 0 || (rect.bottom - rect.top) <= 0) return TRUE;

            // 5. Filtro de barra de tareas y herramientas
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
            if ((exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_NOACTIVATE)) return TRUE;

            // 6. Si el título está vacío, es casi seguro que es una preview o proceso interno
            char title[256];
            if (GetWindowTextA(hwnd, title, sizeof(title)) == 0) return TRUE;

            // Llegados a este punto, la ventana es real, visible y no está minimizada
            data->self->addOrUpdateWindow(hwnd, data->_collisionManager);
            return TRUE;
            }, reinterpret_cast<LPARAM>(&data));
    }

    void addOrUpdateWindow(HWND hwnd, std::shared_ptr<CollisionManager> collisionManager) {
        for (auto& win : activeWindows) {
            if (win->getHwnd() == hwnd) {
                win->updateBounds();
                return;
            }
        }

        auto box = std::make_shared<CollisionBox>();
        auto newWin = std::make_shared<WindowCollidable>(hwnd, box);
        collisionManager->addCollidableEntity(newWin);
        activeWindows.push_back(newWin);
    }

    //GETTER

    /*
    * @brief Obtiene las ventanas activas. Tipo std::vector<std::shared_ptr<WindowCollidable>> 
    */
    std::vector<std::shared_ptr<WindowCollidable>> getActiveWindows() { return activeWindows; };
};
#endif