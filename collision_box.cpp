#include "collision_box.h"

CollisionResult CollisionBox::checkCollision(const std::shared_ptr<CollisionBox> other, const float deltaTime) {
    glm::vec2 pos1 = getNextPosition(deltaTime);
    glm::vec2 pos2 = other->getNextPosition(deltaTime);

    float overlapX = std::min(pos1.x + getSize().x, pos2.x + other->getSize().x) - std::max(pos1.x, pos2.x);
    float overlapY = std::min(pos1.y + getSize().y, pos2.y + other->getSize().y) - std::max(pos1.y, pos2.y);

    if (overlapX > 0 && overlapY > 0) {
        if (overlapX < overlapY) {
            return { true, { (pos1.x < pos2.x ? -1.0f : 1.0f), 0.0f }, overlapX };
        }
        else {
            return { true, { 0.0f, (pos1.y < pos2.y ? -1.0f : 1.0f) }, overlapY };
        }
    }
    return { false, {0,0}, 0 };
}