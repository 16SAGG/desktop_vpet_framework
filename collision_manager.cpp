#include "collision_manager.h"

void CollisionManager :: update() {
    for (size_t i = 0; i < collidableEntities.size(); ++i) {
        for (size_t j = i + 1; j < collidableEntities.size(); ++j) {
            std::shared_ptr<CollisionBox> boxA = collidableEntities[i]->getCollider();
            std::shared_ptr<CollisionBox> boxB = collidableEntities[j]->getCollider();

            CollisionResult collisionRes = boxA -> checkCollision(boxB);

            bool theyAreInSameLayer = boxA->getLayer() == boxB->getLayer();
            bool theyAreIntersecting = collisionRes.intersecting;

            if (theyAreInSameLayer && theyAreIntersecting) {
                collidableEntities[i]->onCollision(collidableEntities[j], collisionRes.normal);
                collidableEntities[j]->onCollision(collidableEntities[i], -collisionRes.normal);
            }
        }
    }
}