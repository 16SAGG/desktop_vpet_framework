#include "window_collidable.h"

const float WINDOW_COLLISION_THICKNESS = 10.0f;
const float LEFT_OFFSET = 80.0f;
const float TOP_OFFSET = 55.0f;

void WindowCollidable :: updateBounds() {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        this->setPosition({ LEFT_OFFSET + (float)rect.left, TOP_OFFSET + (float)rect.top });
        this->getCollider()->setSize({ (float)(rect.right - rect.left), WINDOW_COLLISION_THICKNESS });
    }
}