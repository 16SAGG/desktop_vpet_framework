#pragma once
#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <memory>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <utility>

class Window;

/**
 * @brief Representa a todos los objetos que tienen una representacion en pantalla (visible o invisible)
 */
class Entity : public std::enable_shared_from_this<Entity> {
protected:
    // Posicion base, en caso de que este entity pertenezca a otro aca ira la posicion del padre. Tipo glm::vec2
    glm::vec2 position = { 0.0f, 0.0f };
    
    // Desviacion con respecto a su posicion base. Tipo glm::vec2
    glm::vec2 offset = { 0.0f, 0.0f };
    
    // Dimensiones. Tipo glm::vec2 
    glm::vec2 size = { 0.0f, 0.0f };

    // Es la velocidad maxima. Tipo glm::vec2
    glm::vec2 maxSpeed = { 200, 200 };

    // Es la aceleracion actual del personaje, las propiedades son porcentuales donde '1' equivale al 100%. Tipo glm::vec2
    glm::vec2 acceleration = { 1, 0 };
public:
    virtual ~Entity() = default;

    //Factoria compartida. Permite crear punteros de esta entidad
    template<typename T, typename... Args>
    static std::shared_ptr<T> create(Args&&... args) {
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        return ptr;
    }

    /*
    * @brief Actualiza el comportamiento de la entidad cada frame.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    * @param window Referencia a la ventana que encapsula este objeto. Tipo Window&
    */
    virtual void update(float deltaTime, Window& window) {}

    /*
    * @brief Permite el movimiento de la entindad.
    * @param deltaTime Tiempo transcurrido en segundos desde el último frame. tipo float.
    */
    virtual void move(float deltaTime) {
        setPosition(getNextPosition(deltaTime));
    }

    // SETTERS

    /**
    * @brief Cambia el valor de la posicion de sus hijos.
    * * @param _position Posicion base del padre. Tipo glm::vec2
    */
    virtual void setChildrenPosition(const glm::vec2& _position) { return; };

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
    * @brief Obtiene la velocidad. Tipo glm::vec2
    */
    glm::vec2 getVelocity() const { return acceleration * maxSpeed; }

    /*
    * @brief obtiene la proxima position de la entidad. tipo glm::vec2
    * @param deltaTime tiempo transcurrido entre cada frame. float
    */
    glm::vec2 getNextPosition(float deltaTime) const {
        return getGlobalPosition() + this->getVelocity() * deltaTime;
    }
};
#endif