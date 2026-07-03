#include <memory>

#include "collidable_entity.h"
#include "collision_manager.h"
#include "collision_box.h"

CollidableEntity::~CollidableEntity() {
    try {
        auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());
        CollisionManager::getInstance().removeCollidableEntity(self);
    }
    catch (...) {
    }
};

void CollidableEntity::move(float deltaTime) {
    if (!canMove(deltaTime)) return;

    this->setPosition(getNextPosition(deltaTime));
}

bool CollidableEntity::canMove(float deltaTime) {
    try {
        auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());

        CollisionResult collisionRes = CollisionManager::getInstance().checkCollision(self, deltaTime);

        if (collisionRes.intersecting && collisionRes.otherEntity != nullptr) {
            this->onCollision(collisionRes.otherEntity, collisionRes.normal, collisionRes.penetration);
            collisionRes.otherEntity->onCollision(this, -collisionRes.normal, collisionRes.penetration);
            return false;
        }
    }
    catch (const std::bad_weak_ptr& e) {
        return false;
    }
	
    return true;
}

std::shared_ptr<CollisionBox> CollidableEntity::getCollider() const { return collider; };