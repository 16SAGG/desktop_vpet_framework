#pragma once
#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <glm/glm.hpp>


/**
 * @brief Representa a todos los objetos que tienen una representacion en pantalla (visible o invisible)
 */
class Entity {
protected:
    // Posicion base, en caso de que este entity pertenezca a otro aca ira la posicion del padre. Tipo glm::vec2
    glm::vec2 position = { 0.0f, 0.0f };
    // Desviacion con respecto a su posicion base. Tipo glm::vec2
    glm::vec2 offset = { 0.0f, 0.0f };
    // Dimensiones. Tipo glm::vec2 
    glm::vec2 size = { 0.0f, 0.0f };

    // Determina la velocidad de desplazamiento. Tipo glm::vec2
    glm::vec2 velocity = { 0, 0 };
    // Es la velocidad maxima. Tipo glm::vec2
    glm::vec2 maxSpeed = { 200, 200 };
    // Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    glm::vec2 acceleration = { 1, 0 };

    // Determina si se puede mover. Tipo bool
    bool canMove = true;
public:
    virtual ~Entity() = default;

    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    virtual void setChildrenPosition(const glm::vec2& _position) { return; };

    /*
    * @brief Permite el movimiento de la entindad.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    */
    virtual void move(float deltaTime) {
        if (canMove) setPosition(getNextPosition(deltaTime));
    }

    // SETTERS

    /**
    * @brief Cambia el valor de la variable position y de sus hijos en caso de ser definido.
    * * @param _position Posicion base, en caso de que este entity pertenezca a otro aca ira la posicion del padre. Tipo glm::vec2
    */
    void setPosition(const glm::vec2& _position) { 
        position = _position;
        setChildrenPosition(_position);
    }
    /**
    * @brief Cambia el valor de la variable offset.
    * * @param _offset Desviacion con respecto a su posicion base. Tipo glm::vec2
    */
    void setOffset(const glm::vec2& _offset) { offset = _offset; }
    /**
    * @brief Cambia el valor de la variable size.
    * * @param _size Dimensiones. Tipo glm::vec2 
    */
    void setSize(const glm::vec2& _size) { size = _size; }

    /**
    * @brief Establecer la velocidad maxima.
    * * @param _acceleration Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    */
    void setSpeed(const glm::vec2& _maxSpeed) { maxSpeed = _maxSpeed; };

    /**
    * @brief Establecer acceleration.
    * * @param _acceleration Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    */
    void setAcceleration(const glm::vec2& _acceleration) { acceleration = _acceleration; };

    /**
    * @brief Establece canMove
    * * @param _canMove Determina si se puede mover o no. Tipo bool
    */
    void setCanMove(const bool _canMove) { canMove = _canMove; };

    //GETTERS

    /**
    * @brief Obtiene la posicion. Tipo glm::vec2
    */
    glm::vec2 getPosition() const { return position; }
    /**
    * @brief Obtiene la posicion de dibujado. Tipo glm::vec2
    */
    glm::vec2 getGlobalPosition() const { return position + offset; }
    /**
    * @brief Obtiene las dimensiones. Tipo glm::vec2
    */
    glm::vec2 getSize() const { return size; }
    /**
    * @brief Obtiene las dimensiones. Tipo glm::vec2
    */
    glm::vec2 getVelocity() const { return velocity; }

    /*
    * @brief obtiene la proxima position de la entidad. tipo glm::vec2
    * @param deltaTime tiempo transcurrido entre cada frame. float
    */
    glm::vec2 getNextPosition(float deltaTime) {
        this->velocity = acceleration * maxSpeed;
        return getGlobalPosition() + velocity * deltaTime;
    }
};
#endif