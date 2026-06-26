#include "collidable_entity.h"


CollisionResult CollidableEntity::checkCollision(const std::shared_ptr<CollidableEntity> otherEntity, const float deltaTime) {
    glm::vec2 thisNextPos = this->getNextPosition(deltaTime);
    glm::vec2 otherNextPos = otherEntity->getNextPosition(deltaTime);

    glm::vec2 thisBoxSize = this->getCollider()->getSize();
    glm::vec2 otherBoxSize = otherEntity->getCollider()->getSize();

    float overlapX = std::min(thisNextPos.x + thisBoxSize.x, otherNextPos.x + otherBoxSize.x) - std::max(thisNextPos.x, otherNextPos.x);
    float overlapY = std::min(thisNextPos.y + thisBoxSize.y, otherNextPos.y + otherBoxSize.y) - std::max(thisNextPos.y, otherNextPos.y);

    if (overlapX > 0 && overlapY > 0) {
        if (overlapX < overlapY) {
            return { true, { (thisNextPos.x < otherNextPos.x ? -1.0f : 1.0f), 0.0f }, overlapX };
        }
        else {
            return { true, { 0.0f, (thisNextPos.y < otherNextPos.y ? -1.0f : 1.0f) }, overlapY };
        }
    }
    return { false, {0,0}, 0 };
}

bool CollidableEntity::checkOneWayCollision(const glm::vec2 collisionDir, const CollisionResult collisionRes) const {
    bool itHasASpecificCollisionDir = collisionDir != glm::vec2(0, 0);
    if (itHasASpecificCollisionDir) {
        glm::vec2 velocityNormalized = glm::normalize(this->getVelocity());

        bool movingOppositeX = (velocityNormalized.x * collisionDir.x < -0.5f);
        bool movingOppositeY = (velocityNormalized.y * collisionDir.y < -0.5f);

        if (collisionDir.x != 0 && !movingOppositeX) return false;
        if (collisionDir.y != 0 && !movingOppositeY) return false;
    }
    return true;
}