#include "glm/ext/vector_float2.hpp"

#include "borders_collision_manager.h"
#include "entity_manager.h"

const float THICKNESS = 100.0f;

BordersCollisionManager::BordersCollisionManager(
	const glm::vec2 screenSize,
	const float topMargin,
	const float leftMargin,
	const float rightMargin,
	const float bottomMargin
) {
	auto topBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { screenSize.x + rightMargin + leftMargin, THICKNESS }
			}
		}),
		.entityParams = {
			.position = { -leftMargin, -topMargin - THICKNESS/2 }
		}
	});
	this->borders.push_back(topBorder);

	auto leftBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { THICKNESS, screenSize.y + topMargin + bottomMargin }
			}
		}),
		.entityParams = {
			.position = { -leftMargin - THICKNESS/2, -topMargin }
		}
	});
	this->borders.push_back(leftBorder);

	auto rightBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { THICKNESS, screenSize.y + topMargin + bottomMargin }
			}
		}),
		.entityParams = {
			.position = { screenSize.x + leftMargin + THICKNESS/2, -topMargin }
		}
	});
	this->borders.push_back(rightBorder);

	auto bottomBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { screenSize.x + rightMargin + leftMargin, THICKNESS }
			}
		}),
		.entityParams = {
			.position = { -leftMargin, screenSize.y + bottomMargin + THICKNESS/2 }
		}
	});
	this->borders.push_back(bottomBorder);
}