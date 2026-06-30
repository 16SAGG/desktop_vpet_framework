#include <memory>
#include "glm/ext/vector_float2.hpp"

#include "entity_manager.h"
#include "collision_manager.h"
#include "collidable_entity.h"
#include "character.h"
#include "sprite.h"
#include "collision_box.h"
#include "wall.h"
#include "window.h"
#include "window_collidable.h"

EntityManager& EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

void EntityManager::update(float deltaTime, Window& window) {
    for (auto& entity : entities) {
        entity -> update(deltaTime, window);
    }
}

std::shared_ptr<Character> EntityManager::createCharacter(const CharacterParams& characterParams) {
    std::shared_ptr<Character> character = CollidableEntity::create<Character>(characterParams.sprite, characterParams.collider);

    character->setPosition(characterParams.entityParams.position);
    character->setAcceleration(characterParams.entityParams.acceleration);

    CollisionManager::getInstance().addCollidableEntity(character);
    entities.push_back(character);

    return character;
}

std::shared_ptr<Sprite> EntityManager::createSpritePath(const SpritePathParams& spritePathParams) {
    std::shared_ptr<Sprite> sprite = Sprite::createFromPath(spritePathParams.path);

    sprite = setSpriteParams(sprite, spritePathParams.spriteParams);
    entities.push_back(sprite);

    return sprite;
}

std::shared_ptr<Sprite> EntityManager::createSpriteTexture(const SpriteTextureParams& spriteTextureParams) {
    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(spriteTextureParams.texture);

    sprite = setSpriteParams(sprite, spriteTextureParams.spriteParams);
    entities.push_back(sprite);

    return sprite;
}

std::shared_ptr<Sprite> EntityManager::setSpriteParams(const std::shared_ptr<Sprite> sprite, const SpriteParams& spriteParams) {
    if (spriteParams.frameSize != glm::vec2(0, 0)) sprite->setFrameSize(spriteParams.frameSize);
    if (spriteParams.entityParams.size != glm::vec2(0, 0)) sprite->setSize(spriteParams.entityParams.size);

    sprite->setFrameOffset(spriteParams.frameOffset);
    sprite->setFrameGap(spriteParams.frameGap);

    return sprite;
}

std::shared_ptr<CollisionBox> EntityManager::createCollisionBox(const CollisionBoxParams& collisionBoxParams) {
    std::shared_ptr<CollisionBox> collisionBox = std::make_shared<CollisionBox>();

    collisionBox->setSize(collisionBoxParams.entityParams.size);
    entities.push_back(collisionBox);

    return collisionBox;
}

std::shared_ptr<Wall> EntityManager::createWall(const WallParams& wallParams) {
    std::shared_ptr<Wall> wall = CollidableEntity::create<Wall>(wallParams.collider);

    wall->setPosition(wallParams.entityParams.position);

    CollisionManager::getInstance().addCollidableEntity(wall);
    entities.push_back(wall);

    return wall;
}

std::shared_ptr<WindowCollidable> EntityManager::createWindowCollidable(const WindowCollidableParams& windowCollidableParams) {
    std::shared_ptr<WindowCollidable> windowCollidable = CollidableEntity::create<WindowCollidable>(windowCollidableParams.hwnd, windowCollidableParams.collider);

    CollisionManager::getInstance().addCollidableEntity(windowCollidable);
    entities.push_back(windowCollidable);

    return windowCollidable;
}