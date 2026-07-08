#include <cstdlib>
#include "glm/fwd.hpp"
#include <memory>

#include "desktop_pet.h"
#include "character.h"
#include "utils.h"
#include "collision_box.h"
#include "entity.h"

const float TARGET_X_THRESHOLD_TO_JUMP = 200.0f;
const float TARGET_Y_THRESHOLD_TO_JUMP = 100.0f;
const float WANDER_X_MAX_POSITION_ADDED = 400.0f;
const float SAME_POSITION_EPSILON = 1.0f;
const int MAX_WANDER_FRAMES = 2400;

void DesktopPet::move(float deltaTime) {
	Character::move(deltaTime);

	TargetData targetData{};

	switch (this->getCurrentMovementBehavior())
	{
		case MovementBehavior::FOLLOW_CURSOR: {
			targetData = this->getTargetData(this->mousePosition);
			break;
		}

		case MovementBehavior::FOLLOW_TARGETS: {
			targetData = this->getTargetData(this->targetsToFollow[0]->getGlobalPosition());
			break;
		}

		case MovementBehavior::WANDER:{
			bool timeIsOut = wanderFrames == MAX_WANDER_FRAMES;

			if (timeIsOut) {
				float wanderPositionXRandomLimit1 = this->getGlobalPosition().x - WANDER_X_MAX_POSITION_ADDED;
				float wanderPositionXRandomLimit2 = this->getGlobalPosition().x + WANDER_X_MAX_POSITION_ADDED;

				this->wanderPosition.x = Utils::getInstance().getRandomNumber(wanderPositionXRandomLimit1, wanderPositionXRandomLimit2);
				wanderFrames = 0;
			}
			this->setWanderPosition(glm::vec2(this->wanderPosition.x, this->getGlobalPosition().y));
			wanderFrames++;
			targetData = getTargetData(wanderPosition);
			break;
		}

		default: {
			break;
		}
	}

	this->setDirection(targetData.direction);

	if (this->getIsGrounded()) {
		handleGroundMovement(deltaTime, targetData.distance);
	}
	else {
		handleAirMovement(deltaTime);
	}
}

MovementBehavior DesktopPet::getCurrentMovementBehavior() {
	if (this->followCursorKeyIsPressed) {
		return MovementBehavior::FOLLOW_CURSOR;
	}
	else if (this->targetsToFollow.size() > 0) {
		return MovementBehavior::FOLLOW_TARGETS;
	}
	else {
		return MovementBehavior::WANDER;
	}
}

void DesktopPet::handleGroundMovement(float deltaTime, glm::vec2 distanceToTarget){
	this->setAcceleration({ 1.0f, 0.0f });

	if (-TARGET_Y_THRESHOLD_TO_JUMP >= distanceToTarget.y && std::abs(distanceToTarget.x) <= TARGET_X_THRESHOLD_TO_JUMP) {
		this->jump();
	}
}

void DesktopPet::handleAirMovement(float deltaTime) {
	this->setAcceleration({
		.5f,
		this->acceleration.y - (this->airFriction * deltaTime)
	});
}

void DesktopPet::jump() {
	this->acceleration.y = 1.0f;
}

void DesktopPet::addTargetToFollow(const std::shared_ptr<Entity> newTargetToFollow) {
	this->targetsToFollow.push_back(newTargetToFollow);
}

TargetData DesktopPet::getTargetData(glm::vec2 targetPosition) const {
	glm::vec2 directionToTarget = Utils::getInstance().getNormalizedDirection(this->getGlobalPosition(), targetPosition);
	glm::vec2 distanceToTarget = targetPosition - this->getGlobalPosition();
	return { directionToTarget, distanceToTarget };
}

void DesktopPet::setWanderPosition(const glm::vec2& _wanderPosition) {
	glm::vec2 screenSize = Utils::getInstance().getScreenSize();

	std::shared_ptr<CollisionBox> collider = this->getCollider();
	glm::vec2 wanderLimit = glm::vec2(screenSize.x - collider->getSize().x, screenSize.y - collider->getSize().y);
	glm::vec2 intWanderPosition = Utils::getInstance().convertToIntVector(_wanderPosition);

	if (intWanderPosition.x > wanderLimit.x) this->wanderPosition.x = wanderLimit.x;
	else if (intWanderPosition.x < collider->getSize().x) this->wanderPosition.x = collider->getSize().x;
	else this->wanderPosition.x = intWanderPosition.x;

	if (intWanderPosition.y > wanderLimit.y) this->wanderPosition.y = wanderLimit.y;
	else if (intWanderPosition.y < collider->getSize().x) this->wanderPosition.y = collider->getSize().x;
	else this->wanderPosition.y = intWanderPosition.y;
}