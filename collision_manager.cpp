#include "collision_manager.h"
#include <iostream>

void CollisionManager :: update(const float deltaTime) {
    for (size_t i = 0; i < collidableEntities.size(); ++i) {
        for (size_t j = i + 1; j < collidableEntities.size(); ++j) {
            std::shared_ptr<CollidableEntity> colEntityA = collidableEntities[i];
            std::shared_ptr<CollidableEntity> colEntityB = collidableEntities[j];

            bool oneOfThemIsACharacter = (colEntityA->getCollisionType() == CollisionType::CHARACTER) || (colEntityB->getCollisionType() == CollisionType::CHARACTER);
            bool bothCollisionsAreEnabled = colEntityA->getIsCollisionEnabled() && colEntityB->getIsCollisionEnabled();

            if (oneOfThemIsACharacter && bothCollisionsAreEnabled) {

                CollisionResult collisionRes = colEntityA->checkCollision(colEntityB, deltaTime);

                bool theyAreInSameLayer = colEntityA->getLayer() == colEntityB->getLayer();
                bool theyAreIntersecting = collisionRes.intersecting;
                bool itCollidesWithASolidEntity = colEntityB->getCollisionType() == CollisionType::CHARACTER || colEntityB->getCollisionType() == CollisionType::WALL;
                bool insignificantPenetration = collisionRes.penetration < .01f;

                if (
                    !(theyAreInSameLayer && theyAreIntersecting) || 
                    !itCollidesWithASolidEntity || 
                    insignificantPenetration ||
                    !colEntityA->checkOneWayCollision(colEntityB -> getOneWayCollisionDirection(), collisionRes) // Chequear esto, no me gusta mucho ubicarlo en CollisionBox, quizas sea mejor ubicarlo en collidable entity
                ) continue;

                colEntityA->onCollision(colEntityB, collisionRes.normal, collisionRes);
                colEntityB->onCollision(colEntityA, -collisionRes.normal, collisionRes);
            }
        }
    }
}

void CollisionManager :: addCollidableEntity(std::shared_ptr<CollidableEntity> newCollidableEntity) {
    collidableEntities.push_back(newCollidableEntity);
}

void CollisionManager::removeCollidableEntity(std::shared_ptr<CollidableEntity> entityToRemove) {
    auto iterator = std::remove_if(collidableEntities.begin(), collidableEntities.end(),
        [&entityToRemove](const std::shared_ptr<CollidableEntity>& entity) {
            return entity == entityToRemove;
        });

    if (iterator != collidableEntities.end()) {
        collidableEntities.erase(iterator, collidableEntities.end());
    }
}