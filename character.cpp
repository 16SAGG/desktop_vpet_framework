#include "character.h"

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(std::shared_ptr<CollidableEntity> other, glm::vec2 normal) {
    stopUponImpact(normal);
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
