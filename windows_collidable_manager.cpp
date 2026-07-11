#include <Windows.h>
#include <dwmapi.h>
#include <vector>
#include <memory>
#pragma comment(lib, "dwmapi.lib")

#include "windows_collidable_manager.h"
#include "window_collidable.h"
#include "entity_manager.h"
#include "collision_manager.h"
#include "window.h"

WindowsCollidableManager::WindowsCollidableManager(Window& _window) : window(_window) {}

void WindowsCollidableManager::syncWindows() {
	this->cleanupInactiveWindows();
    this->windowsCachedBorders.clear();
	this->updateAllVisibleWindows();
}

bool WindowsCollidableManager::isValidWindow(HWND hwnd) {
    if (this->window.getWindowHWND() != nullptr && hwnd == this->window.getWindowHWND()) return false;

    if (!IsWindow(hwnd) || IsIconic(hwnd) || !IsWindowVisible(hwnd)) return false;

    int cloaked = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked != 0)
        return false;

    RECT rect;
    GetWindowRect(hwnd, &rect);
    if ((rect.right - rect.left) <= 0 || (rect.bottom - rect.top) <= 0) return false;

    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    if (!(style & WS_VISIBLE)) return false;

    WINDOWPLACEMENT wp{};
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &wp);

    if (wp.showCmd == SW_SHOWMINIMIZED || wp.showCmd == SW_SHOWMAXIMIZED) return false;

    LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    if ((exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_NOACTIVATE)) return false;

    char title[256];
    if (GetWindowTextA(hwnd, title, sizeof(title)) == 0) return false;

    return true;
}

void WindowsCollidableManager::cleanupInactiveWindows() {
    auto& windows = getActiveWindows();

    auto iterator = windows.begin();
    while (iterator != windows.end()) {
        HWND hwnd = (*iterator)->getHwnd();

        if (!isValidWindow(hwnd)) {
            CollisionManager::getInstance().removeCollidableEntity(*iterator);
            iterator = windows.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}

void WindowsCollidableManager::updateAllVisibleWindows() {
    struct CallbackData {
        WindowsCollidableManager* self;
        std::vector<RECT>* rects;
    };

    CallbackData data = { this, &this->windowsCachedBorders };
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        auto data = reinterpret_cast<CallbackData*>(lParam);

        if (!data->self->isValidWindow(hwnd)) return TRUE;

        data->self->addOrUpdateWindow(hwnd);

        RECT rect;
        GetWindowRect(hwnd, &rect);
        data->rects->push_back(rect);

        return TRUE;
    }, reinterpret_cast<LPARAM>(&data));
}

void WindowsCollidableManager::addOrUpdateWindow(HWND hwnd) {
    for (auto& win : this->activeWindows) {
        if (win->getHwnd() == hwnd) {
            win->updateBounds();
            return;
        }
    }

    auto newWin = EntityManager::getInstance().createWindowCollidable({
        .hwnd = hwnd,
        .collider = EntityManager::getInstance().createCollisionBox({})
    });
    this->activeWindows.push_back(newWin);
}