#include <cstdlib>
#include "glm/fwd.hpp"
#include <memory>

#include "desktop_pet.h"
#include "character.h"
#include "utils.h"
#include "collision_box.h"
#include "entity.h"
#include "collidable_entity.h"

const float TARGET_X_THRESHOLD_TO_JUMP = 200.0f;
const float TARGET_Y_THRESHOLD_TO_JUMP = 60.0f;
const float WANDER_X_MAX_POSITION_ADDED = 400.0f;
const float SAME_POSITION_EPSILON = 1.0f;
const float JUMP_COMPENSATION = 25.0f;
const float TARGET_POSITION_REACHED_THRESHOLD = 5.0f;
const int MAX_WANDER_FRAMES = 2400;

void DesktopPet::move(float deltaTime) {
	CollidableEntity::move(deltaTime);

	TargetData targetData = this->getCurrentMovementBehaviorTargetData();
	this->setDirection({ targetData.direction.x, this->direction.y });
	this->handleJump(targetData, deltaTime);

	if (this->getIsGrounded()) this->handleGroundMovement();
	else this->handleAirMovement();
}

TargetData DesktopPet::getCurrentMovementBehaviorTargetData() {
	switch (this->getCurrentMovementBehavior())
	{
		case MovementBehavior::FOLLOW_CURSOR: {
			return this->getTargetData(this->mousePosition);
			break;
		}

		case MovementBehavior::FOLLOW_TARGETS: {
			return this->getTargetData(this->targetsToFollow[0]->getGlobalPosition());
			break;
		}

		case MovementBehavior::STOP: {
			return this->getTargetData(this->getGlobalPosition());
			break;
		}

		case MovementBehavior::WANDER: {
			bool timeIsOut = this->wanderFrames == MAX_WANDER_FRAMES;

			if (timeIsOut) {
				float wanderPositionXRandomLimit1 = this->getGlobalPosition().x - WANDER_X_MAX_POSITION_ADDED;
				float wanderPositionXRandomLimit2 = this->getGlobalPosition().x + WANDER_X_MAX_POSITION_ADDED;

				this->wanderPosition.x = Utils::getInstance().getRandomNumber(wanderPositionXRandomLimit1, wanderPositionXRandomLimit2);
				this->wanderFrames = 0;
			}
			this->setWanderPosition(glm::vec2(this->wanderPosition.x, this->getGlobalPosition().y));
			this->wanderFrames++;
			return this->getTargetData(this->wanderPosition);
			break;
		}

		default: {
			break;
		}
	}
}

MovementBehavior DesktopPet::getCurrentMovementBehavior() {
	if (this->followCursorKeyIsPressed) {
		return MovementBehavior::FOLLOW_CURSOR;
	}
	else if (this->targetsToFollow.size() > 0) {
		return MovementBehavior::FOLLOW_TARGETS;
	}
	else if (this->isStopped) {
		return MovementBehavior::STOP;
	}
	else {
		return MovementBehavior::WANDER;
	}
}

TargetData DesktopPet::getTargetData(glm::vec2 targetPosition) const {
	glm::vec2 directionToTarget = Utils::getInstance().getNormalizedDirection(this->getGlobalPosition(), targetPosition);
	glm::vec2 distanceToTarget = targetPosition - this->getGlobalPosition();
	return { targetPosition, directionToTarget, distanceToTarget };
}

void DesktopPet::setWanderPosition(const glm::vec2& _wanderPosition) {
	glm::vec2 screenSize = Utils::getInstance().getScreenSize();

	std::shared_ptr<CollisionBox> collider = this->getCollider();
	glm::vec2 wanderLimit = glm::vec2(screenSize.x, screenSize.y - collider->getSize().y);
	glm::vec2 intWanderPosition = Utils::getInstance().convertToIntVector(_wanderPosition);

	if (intWanderPosition.x > wanderLimit.x) this->wanderPosition.x = wanderLimit.x;
	else if (intWanderPosition.x < 0) this->wanderPosition.x = 0;
	else this->wanderPosition.x = intWanderPosition.x;

	if (intWanderPosition.y > wanderLimit.y) this->wanderPosition.y = wanderLimit.y;
	else if (intWanderPosition.y < collider->getSize().y) this->wanderPosition.y = collider->getSize().y;
	else this->wanderPosition.y = intWanderPosition.y;
}

void DesktopPet::handleJump(TargetData targetData, float deltaTime) {
	switch (this->currentJumpPhase)
	{
		case JumpPhase::JUMPING: {
			this->applyGravityToDirection(-1);
			this->setAcceleration({ this->acceleration.x, 1 });

			bool isJumpFramesDurationReached = this->jumpFrames >= this->jumpFramesDuration;
			bool isTargetPositionReached = (this->jumpTarget.targetPosition.y - this->getGlobalPosition().y) >= TARGET_POSITION_REACHED_THRESHOLD;
			if (isJumpFramesDurationReached || isTargetPositionReached) {
				this->currentJumpPhase = JumpPhase::FINISHING;
			}

			this->jumpFrames++;

			break;
		}
		case JumpPhase::FINISHING: {
			this->setAcceleration({ this->acceleration.x, this->acceleration.y - this->decrementalJerk.y * deltaTime });

			if (this->acceleration.y <= 0) {
				this->currentJumpPhase = JumpPhase::NONE;
			}

			break;
		}
		default: {
			this->applyGravityToDirection(1);
			this->setAcceleration({ this->acceleration.x, this->acceleration.y + this->incrementalJerk.y * deltaTime });

			if (this->getIsGrounded()) {
				bool targetIsInRangeToJump = -TARGET_Y_THRESHOLD_TO_JUMP >= targetData.distance.y && std::abs(targetData.distance.x) <= TARGET_X_THRESHOLD_TO_JUMP;
				if (targetIsInRangeToJump) {
					this->currentJumpPhase = JumpPhase::JUMPING;
					this->jumpFrames = 0;
					this->jumpTarget = targetData;
				}
			}

			break;
		}
	}
}

void DesktopPet::addTargetToFollow(const std::shared_ptr<Entity> newTargetToFollow) {
	this->targetsToFollow.push_back(newTargetToFollow);
}