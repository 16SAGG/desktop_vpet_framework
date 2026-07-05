#include <memory>
#include "glm/fwd.hpp"

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
	glm::vec2 collisionCorrection = handleCollision(deltaTime);

    this->setPosition(getNextPosition(deltaTime) + collisionCorrection);
}

glm::vec2 CollidableEntity::handleCollision(float deltaTime) {
    try {
        auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());

        CollisionResult collisionRes = CollisionManager::getInstance().checkCollision(self, deltaTime);

        if (collisionRes.intersecting && collisionRes.otherEntity != nullptr) {
            glm::vec2 correction = collisionRes.normal * collisionRes.penetration;
            this->onCollision(collisionRes.otherEntity, collisionRes.normal, collisionRes.penetration);
            return correction;
        }
    }
    catch (const std::bad_weak_ptr& e) {
        return { 0,0 };
    }
	
    return { 0,0 };
}

std::shared_ptr<CollisionBox> CollidableEntity::getCollider() const { return collider; };