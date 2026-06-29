#include "collision_manager.h"
#include "collidable_entity.h"
#include <iostream>

CollisionManager& CollisionManager::getInstance() {
    static CollisionManager instance;
    return instance;
}

CollisionResult CollisionManager :: checkCollision(const std::shared_ptr<CollidableEntity> originEntity, const float deltaTime) const {
    auto snapshot = collidableEntities;

    for (auto& weakOther : snapshot) {
        auto otherEntity = weakOther.lock();
        if (!otherEntity || otherEntity == originEntity || !originEntity->canCollide() || !otherEntity->canCollide()) continue;

        // 1. Verificación básica de solapamiento primero (optimización)
        CollisionResult collisionRes = this->getCollision(originEntity, otherEntity, deltaTime);
        if (!collisionRes.intersecting) continue;

        // 2. Filtros de validación (ahora positivos)
        if (originEntity->getLayer() != otherEntity->getLayer()) continue;

        if (collisionRes.penetration < 0.01f) continue;

        // 3. Tipos de colisión
        bool isSolid = (otherEntity->getCollisionType() == CollisionType::CHARACTER ||
            otherEntity->getCollisionType() == CollisionType::WALL);
        if (!isSolid) continue;

        // 4. One-way logic
        if (!this->getOneWayCollision(originEntity, otherEntity->getOneWayCollisionDirection(), collisionRes)) continue;

        // Si pasamos todos los filtros, es una colisión válida
        return collisionRes;
    }
}

CollisionResult CollisionManager::getCollision(const std::shared_ptr<CollidableEntity> originEntity, const std::shared_ptr<CollidableEntity> otherEntity, const float deltaTime) const{
    glm::vec2 originNextPos = originEntity->getNextPosition(deltaTime);
    glm::vec2 otherNextPos = otherEntity->getNextPosition(deltaTime);

    glm::vec2 originBoxSize = originEntity->getCollider()->getSize();
    glm::vec2 otherBoxSize = otherEntity->getCollider()->getSize();

    float overlapX = std::min(originNextPos.x + originBoxSize.x, otherNextPos.x + otherBoxSize.x) - std::max(originNextPos.x, otherNextPos.x);
    float overlapY = std::min(originNextPos.y + originBoxSize.y, otherNextPos.y + otherBoxSize.y) - std::max(originNextPos.y, otherNextPos.y);

    if (overlapX > 0 && overlapY > 0) {
        if (overlapX < overlapY) {
            return { true, { (originNextPos.x < otherNextPos.x ? -1.0f : 1.0f), 0.0f }, overlapX, otherEntity.get()};
        }
        else {
            return { true, { 0.0f, (originNextPos.y < otherNextPos.y ? -1.0f : 1.0f) }, overlapY, otherEntity.get()};
        }
    }
    return { false, {0,0}, 0 };
}

bool CollisionManager::getOneWayCollision(const std::shared_ptr<CollidableEntity> originEntity, const glm::vec2 collisionDir, const CollisionResult collisionRes) const {
    bool itHasASpecificCollisionDir = collisionDir != glm::vec2(0, 0);

    if (itHasASpecificCollisionDir) {
        glm::vec2 velocityNormalized = glm::normalize(originEntity->getVelocity());

        bool movingOppositeX = (velocityNormalized.x * collisionDir.x < -0.5f);
        bool movingOppositeY = (velocityNormalized.y * collisionDir.y < -0.5f);

        if (collisionDir.x != 0 && !movingOppositeX) return false;
        if (collisionDir.y != 0 && !movingOppositeY) return false;
    }
    return true;
}

void CollisionManager :: addCollidableEntity(const std::shared_ptr<CollidableEntity> newCollidableEntity) {
    collidableEntities.push_back(newCollidableEntity);
}

void CollisionManager::removeCollidableEntity(std::shared_ptr<CollidableEntity> entityToRemove) {
    std::cout << "Remove";
    collidableEntities.erase(
        std::remove_if(collidableEntities.begin(), collidableEntities.end(),
            [&entityToRemove](const std::weak_ptr<CollidableEntity>& weakEntity) {
                auto sharedEntity = weakEntity.lock();

                if (!sharedEntity) return true;

                return sharedEntity == entityToRemove;
            }),
        collidableEntities.end()
    );
}