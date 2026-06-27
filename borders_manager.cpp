#include "borders_manager.h"
#include "wall.h"

const float THICKNESS = 100.0f;

BordersManager::BordersManager(
	const glm::vec2 screenSize,
	const float topMargin,
	const float leftMargin,
	const float rightMargin,
	const float bottomMargin
) {
	auto topBorderCol = std::make_shared<CollisionBox>();
	topBorderCol->setSize({ screenSize.x + rightMargin + leftMargin, THICKNESS });
	auto topBorder = CollidableEntity::create<Wall>(topBorderCol);
	topBorder->setOneWayCollisionDirection({ 0, 1 });
	topBorder->setPosition({ -leftMargin, -topMargin });
	borders.push_back(topBorder);

	auto leftBorderCol = std::make_shared<CollisionBox>();
	leftBorderCol->setSize({ THICKNESS, screenSize.y + topMargin + bottomMargin });
	auto leftBorder = CollidableEntity::create<Wall>(leftBorderCol);
	leftBorder->setOneWayCollisionDirection({ 1, 0 });
	leftBorder->setPosition({ -leftMargin, -topMargin });
	borders.push_back(leftBorder);

	auto rightBorderCol = std::make_shared<CollisionBox>();
	rightBorderCol->setSize({ THICKNESS, screenSize.y + topMargin + bottomMargin});
	auto rightBorder = CollidableEntity::create<Wall>(rightBorderCol);
	rightBorder->setOneWayCollisionDirection({ -1, 0 });
	rightBorder->setPosition({ screenSize.x + leftMargin, -topMargin });
	borders.push_back(rightBorder);

	auto bottomBorderCol = std::make_shared<CollisionBox>();
	bottomBorderCol->setSize({ screenSize.x + rightMargin + leftMargin, THICKNESS });
	auto bottomBorder = CollidableEntity::create<Wall>(bottomBorderCol);
	bottomBorder->setOneWayCollisionDirection({ 0, -1 });
	bottomBorder->setPosition({ -leftMargin, screenSize.y + topMargin });
	borders.push_back(bottomBorder);
}