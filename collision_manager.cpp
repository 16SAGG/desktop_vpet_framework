#include "collision_manager.h"

void CollisionManager :: update(const float deltaTime) {
    for (size_t i = 0; i < collidableEntities.size(); ++i) {
        for (size_t j = i + 1; j < collidableEntities.size(); ++j) {
            std::shared_ptr<CollidableEntity> colEntityA = collidableEntities[i];
            std::shared_ptr<CollidableEntity> colEntityB = collidableEntities[j];

            bool oneOfThemIsACharacter = (colEntityA->getCollisionType() == CollisionType::CHARACTER) || (colEntityB->getCollisionType() == CollisionType::CHARACTER);
            bool bothCollisionsAreEnabled = colEntityA->getIsCollisionEnabled() && colEntityB->getIsCollisionEnabled();

            if (oneOfThemIsACharacter && bothCollisionsAreEnabled) {
                std::shared_ptr<CollisionBox> boxA = colEntityA->getCollider();
                std::shared_ptr<CollisionBox> boxB = colEntityB->getCollider();

                CollisionResult collisionRes = boxA->checkCollision(boxB, deltaTime);

                bool theyAreInSameLayer = colEntityA->getLayer() == colEntityB->getLayer();
                bool theyAreIntersecting = collisionRes.intersecting;

                if (theyAreInSameLayer && theyAreIntersecting) {
                    colEntityA->onCollision(colEntityB, collisionRes.normal, collisionRes);
                    colEntityB->onCollision(colEntityA, -collisionRes.normal, collisionRes);
                }
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