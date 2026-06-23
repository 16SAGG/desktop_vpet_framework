#include "borders_manager.h"

const float THICKNESS = 0.1f;

BordersManager::BordersManager(const glm::vec2 screenSize, const std::shared_ptr<CollisionManager> collisionManager, const float extraSpace) {
	auto topBorderCol = std::make_shared<CollisionBox>();
	topBorderCol->setSize({ screenSize.x + extraSpace, THICKNESS });
	auto topBorder = std::make_shared<Wall>(topBorderCol);
	topBorder->setOneWayCollisionDirection({ 0, 1 });
	topBorder->setPosition({ -extraSpace, -extraSpace });
	collisionManager->addCollidableEntity(topBorder);

	auto leftBorderCol = std::make_shared<CollisionBox>();
	leftBorderCol->setSize({ THICKNESS, screenSize.y + extraSpace});
	auto leftBorder = std::make_shared<Wall>(leftBorderCol);
	leftBorder->setOneWayCollisionDirection({ 1, 0 });
	leftBorder->setPosition({ -extraSpace, -extraSpace });
	collisionManager->addCollidableEntity(leftBorder);

	auto rightBorderCol = std::make_shared<CollisionBox>();
	rightBorderCol->setSize({ THICKNESS, screenSize.y + extraSpace});
	auto rightBorder = std::make_shared<Wall>(rightBorderCol);
	rightBorder->setOneWayCollisionDirection({ -1, 0 });
	rightBorder->setPosition({ screenSize.x + 10 * extraSpace, -extraSpace });
	collisionManager->addCollidableEntity(rightBorder);

	auto bottomBorderCol = std::make_shared<CollisionBox>();
	bottomBorderCol->setSize({ screenSize.x + extraSpace, THICKNESS });
	auto bottomBorder = std::make_shared<Wall>(bottomBorderCol);
	bottomBorder->setOneWayCollisionDirection({ 0, -1 });
	bottomBorder->setPosition({ -extraSpace, screenSize.y + 10 * extraSpace });
	collisionManager->addCollidableEntity(bottomBorder);
}