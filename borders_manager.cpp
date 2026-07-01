#include "glm/ext/vector_float2.hpp"
#include <memory>

#include "borders_manager.h"
#include "wall.h"
#include "collision_box.h"
#include "collidable_entity.h"
#include "entity_manager.h"

const float THICKNESS = 100.0f;

BordersManager::BordersManager(
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
		.oneWayCollisionDirection = { 0, 1 },
		.entityParams = {
			.position = { -leftMargin, -topMargin }
		}
	});
	borders.push_back(topBorder);

	auto leftBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { THICKNESS, screenSize.y + topMargin + bottomMargin }
			}
		}),
		.oneWayCollisionDirection = { 1, 0 },
		.entityParams = {
			.position = { -leftMargin, -topMargin }
		}
	});
	borders.push_back(leftBorder);

	auto rightBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { THICKNESS, screenSize.y + topMargin + bottomMargin }
			}
		}),
		.oneWayCollisionDirection = { -1, 0 },
		.entityParams = {
			.position = { screenSize.x + leftMargin, -topMargin }
		}
	});
	borders.push_back(rightBorder);

	auto bottomBorder = EntityManager::getInstance().createWall({
		.collider = EntityManager::getInstance().createCollisionBox({
			.entityParams = {
				.size = { screenSize.x + rightMargin + leftMargin, THICKNESS }
			}
		}),
		.oneWayCollisionDirection = { 0, -1 },
		.entityParams = {
			.position = { -leftMargin, screenSize.y + bottomMargin }
		}
	});
	borders.push_back(bottomBorder);
}