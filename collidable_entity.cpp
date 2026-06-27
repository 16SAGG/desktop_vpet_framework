#include<iostream>

#include "collidable_entity.h"

void CollidableEntity::move(float deltaTime) {
    this->updateCollisionCooldown(deltaTime);

    if (this->canCollide()) {
        try {
            auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());

            CollisionResult collisionRes = CollisionManager::getInstance().checkCollision(self, deltaTime);

            if (collisionRes.intersecting && collisionRes.otherEntity != nullptr) {
                this->onCollision(collisionRes.otherEntity, collisionRes.normal, collisionRes);
                this->startCollisionCooldown();
                return;
            }
        }
        catch (const std::bad_weak_ptr& e) {
            return;
        }
    }
    
    this->setPosition(getNextPosition(deltaTime));
}