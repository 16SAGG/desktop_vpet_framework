#include "character.h"

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 collisionNormalized) {
    bool itCollidesWithASolidEntity = other->getCollisionType() == CollisionType::CHARACTER || other->getCollisionType() == CollisionType::WALL;
    
    if (!itCollidesWithASolidEntity) return;
    
    bool itIsAWall = other->getCollisionType() == CollisionType::WALL;
    if (itIsAWall) {
        std::shared_ptr<Wall> wall = std::dynamic_pointer_cast<Wall>(other);

        if (wall) {
            glm::vec2 wallCollisionDir = wall->getOneWayCollisionDirection();

            bool wallHasASpecificCollisionDir = wallCollisionDir != glm::vec2(0, 0);
            if (wallHasASpecificCollisionDir) {
                glm::vec2 velocityNormalized = glm::normalize(velocity);
                
                bool characterIsMovingToOneWayCollision = glm::dot(velocityNormalized, wallCollisionDir) <= .5f;
                if (!characterIsMovingToOneWayCollision) return;
            }
        }
    }
    
    stopUponImpact(collisionNormalized);
}

void Character::move(float deltaTime) {
    this->velocity = acceleration * maxSpeed;

    setPosition(getPosition() + velocity * deltaTime);
}

void Character::stopUponImpact(glm::vec2 normal) {
    if (normal.x != 0) {
        this->acceleration.x = 0;
    }
    else if (normal.y != 0) {
        this->acceleration.y = 0;
    }
}
