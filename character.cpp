#include "character.h"

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const std::shared_ptr<CollidableEntity> other, const glm::vec2 collisionNormalized, const CollisionResult collisionRes) {
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
