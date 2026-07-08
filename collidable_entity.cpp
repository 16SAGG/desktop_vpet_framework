#include <memory>
#include <vector>
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
    glm::vec2 correction = { 0, 0 };
    try {
        auto self = std::static_pointer_cast<CollidableEntity>(shared_from_this());

        std::vector<CollisionResult> results = CollisionManager::getInstance().checkCollision(self, deltaTime);

        for (const auto& collisionRes : results){
            if (collisionRes.intersecting && collisionRes.otherEntity != nullptr) {
                glm::vec2 newCorrection = collisionRes.normal * collisionRes.penetration;
                
                this->onCollision(collisionRes.otherEntity, collisionRes.normal, collisionRes.penetration);
                collisionRes.otherEntity->onCollision(this, -collisionRes.normal, collisionRes.penetration);

                correction += newCorrection;
            }
        }
    }
    catch (const std::bad_weak_ptr& e) {}
	
    return correction;
}

std::shared_ptr<CollisionBox> CollidableEntity::getCollider() const { return collider; };