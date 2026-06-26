#include "borders_manager.h"

const float THICKNESS = 100.0f;

BordersManager::BordersManager(
	const glm::vec2 screenSize,
	const std::shared_ptr<CollisionManager> collisionManager,
	const float topMargin,
	const float leftMargin,
	const float rightMargin,
	const float bottomMargin
) {
	auto topBorderCol = std::make_shared<CollisionBox>();
	topBorderCol->setSize({ screenSize.x + rightMargin + leftMargin, THICKNESS });
	auto topBorder = std::make_shared<Wall>(topBorderCol);
	topBorder->setOneWayCollisionDirection({ 0, 1 });
	topBorder->setPosition({ -leftMargin, -topMargin });
	collisionManager->addCollidableEntity(topBorder);

	auto leftBorderCol = std::make_shared<CollisionBox>();
	leftBorderCol->setSize({ THICKNESS, screenSize.y + topMargin + bottomMargin });
	auto leftBorder = std::make_shared<Wall>(leftBorderCol);
	leftBorder->setOneWayCollisionDirection({ 1, 0 });
	leftBorder->setPosition({ -leftMargin, -topMargin });
	collisionManager->addCollidableEntity(leftBorder);

	auto rightBorderCol = std::make_shared<CollisionBox>();
	rightBorderCol->setSize({ THICKNESS, screenSize.y + topMargin + bottomMargin});
	auto rightBorder = std::make_shared<Wall>(rightBorderCol);
	rightBorder->setOneWayCollisionDirection({ -1, 0 });
	rightBorder->setPosition({ screenSize.x + leftMargin, -topMargin });
	collisionManager->addCollidableEntity(rightBorder);

	auto bottomBorderCol = std::make_shared<CollisionBox>();
	bottomBorderCol->setSize({ screenSize.x + rightMargin + leftMargin, THICKNESS });
	auto bottomBorder = std::make_shared<Wall>(bottomBorderCol);
	bottomBorder->setOneWayCollisionDirection({ 0, -1 });
	bottomBorder->setPosition({ -leftMargin, screenSize.y + topMargin });
	collisionManager->addCollidableEntity(bottomBorder);
}