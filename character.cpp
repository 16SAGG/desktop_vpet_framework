#include <memory>
#include "glm/fwd.hpp"

#include "character.h"
#include "window.h"
#include "sprite.h"
#include "collidable_entity.h"
#include "collision_box.h"
#include "renderer_2d.h"
#include "entity.h"

void Character::update(float deltaTime, Window& window) {
    Entity::update(deltaTime, window);

    this->isGrounded = false;
    this->move(deltaTime);

    Renderer2D::getInstance().draw(this->sprite, window.getProjection());
}

void Character::move(float deltaTime) {
    CollidableEntity::move(deltaTime);

    this->applyGravityToDirection(1);

    if (this->getIsGrounded()) this->handleGroundMovement();
    else this->handleAirMovement();
}

void Character::applyGravityToDirection(float value) {
    glm::vec2 newDirection = { 0,0 };

    if (this->gravity.x != 0.0f) newDirection.x = value;
    else newDirection.x = this->direction.x;

    if (this->gravity.y != 0.0f) newDirection.y = value;
    else newDirection.y = this->direction.y;

    this->setDirection(newDirection);
}

void Character::handleGroundMovement() { this->setAcceleration({ 1.0f, this->acceleration.y }); }

void Character::handleAirMovement() { this->setAcceleration({ .5f, this->acceleration.y }); }

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) {
    if (!other) return;

	bool isGravityCollision = (-this->gravity == collisionNormalized);
	if (isGravityCollision) {
		this->isGrounded = true;
	}
}

void Character::setChildrenPosition(const glm::vec2& _position) {
    this->sprite->setPosition(_position);
    this->collider->setPosition(_position);
}