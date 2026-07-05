#include <cstdlib>
#include "glm/fwd.hpp"
#include <iostream>

#include "desktop_pet.h"
#include "character.h"
#include "window.h"
#include "utils.h"

const float TARGET_X_THRESHOLD_TO_JUMP = 100.0f;
const float TARGET_Y_THRESHOLD_TO_JUMP = -100.0f;

void DesktopPet::applyFriction(const float deltaTime) {
	if (friction.x > 0.0f) {
		acceleration.x -= friction.x * deltaTime;
		if (acceleration.x < 0.0f) acceleration.x = 0.0f;
	}

	if (friction.y > 0.0f) {
		acceleration.y -= friction.y * deltaTime;
		if (acceleration.y < 0.0f) acceleration.y = 0.0f;
	}
}

void DesktopPet::jump() {
	this->acceleration.y = 1.0f;
}

void DesktopPet::update(float deltaTime, Window& window) {
	Character::update(deltaTime, window);

	glm::vec2 directionToTarget = Utils::getInstance().getNormalizedDirection(this->getGlobalPosition(), mousePosition);
	this->setDirection(directionToTarget);
	glm::vec2 distanceToTarget = mousePosition - this->getGlobalPosition();

	if (this->getIsGrounded()) {
		this->acceleration.x = 1.0f;
		this->acceleration.y = 0.0f;

		if (TARGET_Y_THRESHOLD_TO_JUMP >= distanceToTarget.y && std::abs(distanceToTarget.x) <= TARGET_X_THRESHOLD_TO_JUMP) {
			jump();
		}
	}
	else {
		this->acceleration.x = .25f;
	}

	applyFriction(deltaTime);
}