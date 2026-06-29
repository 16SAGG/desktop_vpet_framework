#pragma once
#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include <memory>
#include "glm/fwd.hpp"

#include "collidable_entity.h"

class Sprite;
class CollisionBox;
class Window;
class CollisionResult;

/**
* @brief Es una caja empleada para detectar el contacto con otros
*/
class Character : public CollidableEntity
{
private:

    // Referencia al sprite del character. Tipo Sprite
    std::shared_ptr<Sprite> sprite;
public:

    /**
    * @brief Constructor de Character
    ** @param _sprite Referencia al sprite del character. Tipo Sprite
    * @param _collider Referencia al CollisionBox. Tipo CollisionBox
    */
    Character(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider); 

    /*
    * @brief Actualiza el comportamiento de la entidad cada frame.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    * @param window Referencia a la ventana que encapsula este objeto. Tipo Window
    */
    void update(float deltaTime, Window& window) override;

    /**
    * @brief Determina el comportamiento de esta entiendad a colisionar.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param collisionNormalized La direccion de la colision. Tipo glm::vec2
    * @param penetration Determina cuanto fue la penetracion entre los dos objetos al colisionar. Tipo float
    */
    void onCollision(const CollidableEntity* other, const glm::vec2 collisionNormalized, const float penetration) override;

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es detener el desplazamiento en la direccion a la que colisiona.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void stopUponImpact(const CollidableEntity* other, glm::vec2 normal);

    /*
    * @brief Es la reaccion de este cuerpo al colisionar con un objeto solido. Su efecto es rebotar.
    * @param other Referencia al CollidableEntity con el que colisiono. Tipo std::shared_ptr<CollidableEntity>
    * @param normal. Es el vector normal que indica donde se colisiono. glm::vec2
    */
    void bounce(const CollidableEntity* other, glm::vec2 normal);

    // GETTERS

    /*
    * @brief Obtinene una referencia al sprite. Tipo std::shared_ptr<Sprite>
    */
    std::shared_ptr<Sprite> getSprite() { return sprite; };

    // SETTERS
    
    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    void setChildrenPosition(const glm::vec2& _position);
};
#endif