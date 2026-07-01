#include <memory>
#include "glm/fwd.hpp"

#include "character.h"
#include "window.h"
#include "sprite.h"
#include "collidable_entity.h"
#include "collision_box.h"
#include "renderer_2d.h"

void Character::update(float deltaTime, Window& window) {
    move(deltaTime);
    Renderer2D::getInstance().draw(sprite, window.getProjection());
}

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) {
    if (!other) return;

    glm::vec2 correction = collisionNormalized * penetration;
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

void Character::setChildrenPosition(const glm::vec2& _position) {
    sprite->setPosition(_position);
    collider->setPosition(_position);
}