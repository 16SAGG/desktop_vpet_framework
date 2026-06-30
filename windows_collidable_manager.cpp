#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include "windows_collidable_manager.h"
#include "window_collidable.h"
#include "entity_manager.h"
#include "collision_manager.h"

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

        int cloaked = 0;
        if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked != 0)
            return TRUE;

        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        if (!(style & WS_VISIBLE)) return TRUE;

        WINDOWPLACEMENT wp{};
        wp.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(hwnd, &wp);

        if (wp.showCmd == SW_SHOWMINIMIZED) return TRUE;

        RECT rect;
        GetWindowRect(hwnd, &rect);
        if ((rect.right - rect.left) <= 0 || (rect.bottom - rect.top) <= 0) return TRUE;

        LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
        if ((exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_NOACTIVATE)) return TRUE;

        char title[256];
        if (GetWindowTextA(hwnd, title, sizeof(title)) == 0) return TRUE;

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

    auto newWin = EntityManager::getInstance().createWindowCollidable({
        .hwnd = hwnd,
        .collider = EntityManager::getInstance().createCollisionBox({})
    });
    activeWindows.push_back(newWin);
}