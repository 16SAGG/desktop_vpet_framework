#include "windows_collidable_manager.h"

void WindowsCollidableManager :: syncWindows() {
	this->cleanupInactiveWindows();
	this->updateAllVisibleWindows();
}

void WindowsCollidableManager :: cleanupInactiveWindows() {
    auto& windows = getActiveWindows();

    auto iterator = windows.begin();
    while (iterator != windows.end()) {
        HWND hwnd = (*iterator)->getHwnd();

        if (!IsWindow(hwnd)) {
            CollisionManager::getInstance().removeCollidableEntity(*iterator);
            iterator = windows.erase(iterator);
            continue;
        }

        // 2. Detección de minimización clásica (IsIconic)
        // 3. Detección por DWM (Cloaked)
        int cloaked = 0;
        DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));

        if (IsIconic(hwnd) || cloaked != 0 || !IsWindowVisible(hwnd)) {
            CollisionManager::getInstance().removeCollidableEntity(*iterator);
            iterator = windows.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}

void WindowsCollidableManager :: updateAllVisibleWindows() {
    struct CallbackData {
        WindowsCollidableManager* self;
    };

    CallbackData data = { this };
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
        data->self->addOrUpdateWindow(hwnd);
        return TRUE;
    }, reinterpret_cast<LPARAM>(&data));
}

void WindowsCollidableManager :: addOrUpdateWindow(HWND hwnd) {
    for (auto& win : activeWindows) {
        if (win->getHwnd() == hwnd) {
            win->updateBounds();
            return;
        }
    }

    auto box = std::make_shared<CollisionBox>();
    auto newWin = CollidableEntity::create<WindowCollidable>(hwnd, box);
    activeWindows.push_back(newWin);
}