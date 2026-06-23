#include "borders_manager.h"

const float THICKNESS = 0.1f;

BordersManager::BordersManager(const glm::vec2 screenSize, const std::shared_ptr<CollisionManager> collisionManager, const float extraSpace) {
	auto topBorderCol = std::make_shared<CollisionBox>();
	topBorderCol->setPosition({ -extraSpace, -extraSpace });
	topBorderCol->setSize({ screenSize.x + extraSpace, THICKNESS });
	auto topBorder = std::make_shared<Wall>(topBorderCol);
	collisionManager->addCollidableEntity(topBorder);

	auto leftBorderCol = std::make_shared<CollisionBox>();
	leftBorderCol->setPosition({ -extraSpace, -extraSpace });
	leftBorderCol->setSize({ THICKNESS, screenSize.y + extraSpace});
	auto leftBorder = std::make_shared<Wall>(leftBorderCol);
	collisionManager->addCollidableEntity(leftBorder);

	auto rightBorderCol = std::make_shared<CollisionBox>();
	rightBorderCol->setPosition({ screenSize.x + 10 * extraSpace, -extraSpace });
	rightBorderCol->setSize({ THICKNESS, screenSize.y + extraSpace});
	auto rightBorder = std::make_shared<Wall>(rightBorderCol);
	collisionManager->addCollidableEntity(rightBorder);

	auto bottomBorderCol = std::make_shared<CollisionBox>();
	bottomBorderCol->setPosition({ -extraSpace, screenSize.y + 10 * extraSpace });
	bottomBorderCol->setSize({ screenSize.x + extraSpace, THICKNESS });
	auto bottomBorder = std::make_shared<Wall>(bottomBorderCol);
	collisionManager->addCollidableEntity(bottomBorder);
}