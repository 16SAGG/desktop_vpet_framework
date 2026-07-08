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

Character::Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
    CollidableEntity(CollisionType::CHARACTER),
    sprite(_sprite)
{
    this->collider = _collider;
}

void Character::onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) {
    if (!other) return;

	bool isGravityCollision = (-getGravityNormalized() == collisionNormalized);
	if (isGravityCollision) {
		this->isGrounded = true;
        return;
	}
}

void Character::setChildrenPosition(const glm::vec2& _position) {
    sprite->setPosition(_position);
    collider->setPosition(_position);
}