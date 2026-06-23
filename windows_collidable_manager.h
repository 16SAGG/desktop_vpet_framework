#pragma once
#ifndef WINDOWS_COLLIDABLE_MANAGER_CLASS_H
#define WINDOWS_COLLIDABLE_MANAGER_CLASS_H

#include <windows.h>
#include <iostream>
#include <cstdlib>

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
        std::cout << activeWindows.size();
        system("cls");

        struct CallbackData {
            WindowsCollidableManager* self;
            std::shared_ptr<CollisionManager> _collisionManager;
        };

        CallbackData data = { this, collisionManager };
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            auto data = reinterpret_cast<CallbackData*>(lParam);

            // --- FILTROS DE VALIDACIÓN ---

            // 1. ¿Es visible?
            if (!IsWindowVisible(hwnd)) return TRUE;

            // 2. ¿Está minimizada? (IsIconic devuelve true si está minimizada)
            if (IsIconic(hwnd)) return TRUE;

            // 3. Ignorar ventanas sin título o sin dimensiones (muy útil para evitar previews)
            char title[256];
            GetWindowTextA(hwnd, title, sizeof(title));
            if (strlen(title) == 0) return TRUE;

            // 4. Ignorar "Program Manager" (el escritorio mismo)
            if (strcmp(title, "Program Manager") == 0) return TRUE;

            // 5. Ignorar ventanas de herramienta o invisibles al usuario
            LONG style = GetWindowLong(hwnd, GWL_STYLE);
            if ((style & WS_DISABLED) || !(style & WS_VISIBLE)) return TRUE;

            char className[256];
            GetClassNameA(hwnd, className, sizeof(className));
            // Las previews de la barra suelen ser 'DwmThumbnail' o similares
            if (strcmp(className, "DwmThumbnail") == 0) return TRUE;

            // 1. Obtener estilos extendidos
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

            // 2. Filtro: WS_EX_TOOLWINDOW suele ocultar ventanas de la barra de tareas 
            // y muchas de estas previews tienen este estilo.
            if (exStyle & WS_EX_TOOLWINDOW) return TRUE;

            // 3. Filtro: Si la ventana no tiene un "propietario", a veces son ventanas fantasma de sistema.
            if (GetWindow(hwnd, GW_OWNER) != NULL) return TRUE;

            // 4. Filtro por Título: Muchas previews tienen el mismo título que la ventana real, 
            // pero a veces el sistema les asigna un título vacío o "Default IME".
            GetWindowTextA(hwnd, title, sizeof(title));
            if (strcmp(title, "Default IME") == 0) return TRUE;

            // Si pasa todos los filtros, es una ventana real
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
};
#endif