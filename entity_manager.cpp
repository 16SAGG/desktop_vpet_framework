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
#include "renderer_2d.h"
#include "entity.h"
#include "desktop_pet.h"

EntityManager& EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

void EntityManager::update(float deltaTime, Window& window) {
    for (auto& entity : entities) {
        entity -> update(deltaTime, window);
		Renderer2D::getInstance().drawColoredEntity(entity, window.getProjection(), { 1, 0, 0, 1 });
    }
}

std::shared_ptr<Entity> EntityManager::setEntityParams(const std::shared_ptr<Entity> entity, const EntityParams& entityParams) {
    if (entityParams.size != glm::vec2(0, 0)) entity->setSize(entityParams.size);
    if (entityParams.position != glm::vec2(0, 0)) entity->setPosition(entityParams.position);
    if (entityParams.offset != glm::vec2(0, 0)) entity->setOffset(entityParams.offset);
    if (entityParams.acceleration != glm::vec2(0, 0)) entity->setAcceleration(entityParams.acceleration);
    if (entityParams.direction != glm::vec2(0, 0)) entity->setDirection(entityParams.direction);
	if (entityParams.maxSpeed != glm::vec2(0, 0)) entity->setMasSpeed(entityParams.maxSpeed);

    return entity;
}

std::shared_ptr<Character> EntityManager::setCharacterParams(const std::shared_ptr<Character> character, const CharacterParams& characterParams) {
	if (characterParams.gravity != glm::vec2(0, 0)) character->setGravity(characterParams.gravity);

	return std::static_pointer_cast<Character>(setEntityParams(character, characterParams.entityParams));
}

std::shared_ptr<Character> EntityManager::createCharacter(const CharacterParams& characterParams) {
    std::shared_ptr<Character> character = CollidableEntity::create<Character>(characterParams.sprite, characterParams.collider);

	character = setCharacterParams(character, characterParams);

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

    sprite->setFrameOffset(spriteParams.frameOffset);
    sprite->setFrameGap(spriteParams.frameGap);

	return std::static_pointer_cast<Sprite>(setEntityParams(sprite, spriteParams.entityParams));
}

std::shared_ptr<CollisionBox> EntityManager::createCollisionBox(const CollisionBoxParams& collisionBoxParams) {
    std::shared_ptr<CollisionBox> collisionBox = std::make_shared<CollisionBox>();

    collisionBox = std::static_pointer_cast<CollisionBox>(setEntityParams(collisionBox, collisionBoxParams.entityParams));
    entities.push_back(collisionBox);

    return collisionBox;
}

std::shared_ptr<Wall> EntityManager::createWall(const WallParams& wallParams) {
    std::shared_ptr<Wall> wall = CollidableEntity::create<Wall>(wallParams.collider);

    wall->setOneWayCollisionDirection(wallParams.oneWayCollisionDirection);
	wall = std::static_pointer_cast<Wall>(setEntityParams(wall, wallParams.entityParams));

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

std::shared_ptr<DesktopPet> EntityManager::createDesktopPet(const DesktopPetParams& desktopPetParams) {
	std::shared_ptr<DesktopPet> desktopPet = CollidableEntity::create<DesktopPet>(desktopPetParams.characterParams.sprite, desktopPetParams.characterParams.collider);
    
	desktopPet->setAirFriction(desktopPetParams.airFriction);

	desktopPet = std::static_pointer_cast<DesktopPet>(setCharacterParams(desktopPet, desktopPetParams.characterParams));

	CollisionManager::getInstance().addCollidableEntity(desktopPet);
	entities.push_back(desktopPet);

	return desktopPet;
}