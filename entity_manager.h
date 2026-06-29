#pragma once
#ifndef ENTITY_MANAGER_CLASS_H
#define ENTITY_MANAGER_CLASS_H

#include <vector>
#include <memory>
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include <Windows.h>

class Entity;
class Character;
class Sprite;
class CollisionBox;
class Texture;
class Renderer2D;
class Wall;
class Window;
class WindowCollidable;

//Parametros de creacion de Entidad
struct EntityParams {
    glm::vec2 size = { 0,0 };
    glm::vec2 position = { 0,0 };
    glm::vec2 acceleration = { 0,0 };
};

//Parametros de creacion de Character
struct CharacterParams {
    std::shared_ptr<Sprite> sprite = nullptr;
    std::shared_ptr<CollisionBox> collider = nullptr;
    EntityParams entityParams;
};

//Parametros de creacion de Sprite (BASE)
struct SpriteParams {
    glm::vec2 frameSize = { 0,0 };
    glm::vec2 frameOffset = { 0,0 };
    glm::vec2 frameGap = { 0,0 };
    EntityParams entityParams;
};

//Parametros de creacion de Sprite (PATH)
struct SpritePathParams {
    const char* path;
    SpriteParams spriteParams;
};

//Parametros de creacion de Sprite (Texture)
struct SpriteTextureParams{
    std::shared_ptr<Texture> texture = nullptr;
    SpriteParams spriteParams;
};

//Parametros de creacion de CollisionBox
struct CollisionBoxParams {
    EntityParams entityParams;
};

//Parametros de creacion de Wall
struct WallParams {
    std::shared_ptr<CollisionBox> collider = nullptr;
    glm::vec2 oneWayCollisionDirection;
    EntityParams entityParams;
};

//Parametros de creacion de WindowCollidable
struct WindowCollidableParams {
    HWND hwnd;
    std::shared_ptr<CollisionBox> collider = nullptr;
};

/**
* @brief Crea y gestiona todas las entidades
*/
class EntityManager
{
private:
    // Lista de todas las entidades. Tipo std::vector<std::shared_ptr<Entity>>
    std::vector<std::shared_ptr<Entity>> entities;

    /**
    * @brief Constructor de EntityManager
    */
    EntityManager() {};
public:
    /**
    * @brief Obtiene la unica instancia de EntityManager
    */
    static EntityManager& getInstance();

    /*
    * @brief Recorre cada entidad y ejecuta la funcion update de cada uno.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    * @param window Puntero a la ventana de GLFW que controla el bucle. Tipo Window
    */
    void update(float deltaTime, Window& window);

    /**
    * @brief Crea una entidad Character. Tipo std::shared_ptr<Character>
    * @param params Parametros de creacion de Character. Tipo CharacterParamas&
    */
    std::shared_ptr<Character> createCharacter(const CharacterParams& characterParams );

    /**
    * @brief Crea una entidad Sprite usando un Path para crear una textura. Tipo std::shared_ptr<Sprite>
    * @param params Parametros de creacion de Sprite. Tipo SpritePathParams&
    */
    std::shared_ptr<Sprite> createSpritePath(const SpritePathParams& spritePathParams);

    /**
    * @brief Crea una entidad Sprite usando una textura previamente creada. Tipo std::shared_ptr<Sprite>
    * @param params Parametros de creacion de Sprite. Tipo SpriteTextureParamas&
    */
    std::shared_ptr<Sprite> createSpriteTexture(const SpriteTextureParams& spriteTextureParams);

    /**
    * @brief Establece los parametros base del sprite
    * @param sprite Previamente creado al que se le aplicaran los cambios. Tipo Sprite
    * @param params Parametros de creacion de Sprite. Tipo SpriteParamas&
    */
    std::shared_ptr<Sprite> setSpriteParams(const std::shared_ptr<Sprite> sprite, const SpriteParams& spriteParams);

    /**
    * @brief Crea una entidad CollisionBox. Tipo std::shared_ptr<CollisionBox>
    * @param params Parametros de creacion de CollisionBox. Tipo CollisionBox&
    */
    std::shared_ptr<CollisionBox> createCollisionBox(const CollisionBoxParams& collisionBoxParams);

    /**
    * @brief Crea una entidad Wall. Tipo std::shared_ptr<Wall>
    * @param params Parametros de creacion de Wall. Tipo WallParamas&
    */
    std::shared_ptr<Wall> createWall(const WallParams& wallParams);

    /**
    * @brief Crea una entidad WindowCollidable. Tipo std::shared_ptr<WindowCollidable>
    * @param params Parametros de creacion de WindowCollidable. Tipo WindowCollidableParamas&
    */
    std::shared_ptr<WindowCollidable> createWindowCollidable(const WindowCollidableParams& windowCollidableParams);
};
#endif