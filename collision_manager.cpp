#include "collision_manager.h"

void CollisionManager :: update() {
    for (size_t i = 0; i < collidableEntities.size(); ++i) {
        for (size_t j = i + 1; j < collidableEntities.size(); ++j) {
            std::shared_ptr<CollidableEntity> colEntityA = collidableEntities[i];
            std::shared_ptr<CollidableEntity> colEntityB = collidableEntities[j];

            bool oneOfThemIsACharacter = (colEntityA->getCollisionType() == CollisionType::CHARACTER) || (colEntityB->getCollisionType() == CollisionType::CHARACTER);
            
            if (oneOfThemIsACharacter) {
                std::shared_ptr<CollisionBox> boxA = colEntityA->getCollider();
                std::shared_ptr<CollisionBox> boxB = colEntityB->getCollider();

                CollisionResult collisionRes = boxA->checkCollision(boxB);

                bool theyAreInSameLayer = boxA->getLayer() == boxB->getLayer();
                bool theyAreIntersecting = collisionRes.intersecting;

                if (theyAreInSameLayer && theyAreIntersecting) {
                    colEntityA->onCollision(colEntityB, collisionRes.normal, collisionRes);
                    colEntityB->onCollision(colEntityA, -collisionRes.normal, collisionRes);
                }
            }
        }
    }
}