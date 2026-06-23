#include "window_collidable.h"

void WindowCollidable :: updateBounds() {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        this->setPosition({ (float)rect.left, (float)rect.top });
        this->getCollider()->setSize({ (float)(rect.right - rect.left), (float)(rect.bottom - rect.top) });
    }
}