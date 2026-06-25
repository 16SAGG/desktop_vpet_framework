#include "character.h"
#include <iostream>

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const std::shared_ptr<CollidableEntity> other, const glm::vec2 collisionNormalized, const CollisionResult collisionRes) {
    bool itCollidesWithASolidEntity = other->getCollisionType() == CollisionType::CHARACTER || other->getCollisionType() == CollisionType::WALL;
    bool insignificantPenetration = collisionRes.penetration < .01f;

    if (!itCollidesWithASolidEntity || insignificantPenetration) return;
    
    bool itIsAWall = other->getCollisionType() == CollisionType::WALL;
    if (itIsAWall) {
        std::shared_ptr<Wall> wall = std::dynamic_pointer_cast<Wall>(other);

        if (wall) {
            glm::vec2 wallCollisionDir = wall->getOneWayCollisionDirection();

            bool wallHasASpecificCollisionDir = wallCollisionDir != glm::vec2(0, 0);
            if (wallHasASpecificCollisionDir) {
                glm::vec2 velocityNormalized = glm::normalize(velocity);

                bool movingOppositeX = (velocityNormalized.x * wallCollisionDir.x < -0.5f);
                bool movingOppositeY = (velocityNormalized.y * wallCollisionDir.y < -0.5f);

                if (wallCollisionDir.x != 0 && !movingOppositeX) return;
                if (wallCollisionDir.y != 0 && !movingOppositeY) return;
            }
        }
    }
    
    glm::vec2 correction = collisionNormalized * collisionRes.penetration;
    this->setPosition(this->getPosition() + correction);

    bounce(other, collisionNormalized);
}

void Character::stopUponImpact(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) {
    if (normal.x != 0) {
        this->acceleration.x = 0;
    }
    else if (normal.y != 0) {
        this->acceleration.y = 0;
    }
}

void Character::bounce(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) {
    if (normal.x != 0) {
        this->acceleration.x = -this->acceleration.x;
    }
    else if (normal.y != 0) {
        this->acceleration.y = -this->acceleration.y;
    }
}
