#include "character.h"
#include "window.h"

void Character::update(float deltaTime, Window& window) {
    move(deltaTime);
    Renderer2D::getInstance().draw(sprite, window.projection);
}

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const CollisionResult collisionRes) {
    if (!other) return;

    glm::vec2 correction = collisionNormalized * collisionRes.penetration;
    this->setPosition(this->getPosition() + correction);

    bounce(other, collisionNormalized);
}

void Character::stopUponImpact(const CollidableEntity* other, glm::vec2 normal) {
    if (normal.x != 0) {
        this->acceleration.x = 0;
    }
    else if (normal.y != 0) {
        this->acceleration.y = 0;
    }
}

void Character::bounce(const CollidableEntity* other, glm::vec2 normal) {
    if (normal.x != 0) {
        this->acceleration.x = -this->acceleration.x;
    }
    else if (normal.y != 0) {
        this->acceleration.y = -this->acceleration.y;
    }
}
