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

public:
    virtual ~Entity() = default;

    // SETTERS

    /**
    * @brief Cambia el valor de la variable position.
    * * @param _position Posicion base, en caso de que este entity pertenezca a otro aca ira la posicion del padre. Tipo glm::vec2
    */
    void setPosition(const glm::vec2& _position) { position = _position; }
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

    //GETTERS

    /**
    * @brief Obtiene la posicion real. Tipo glm::vec2
    */
    glm::vec2 getGlobalPosition() const { return position + offset; }
    /**
    * @brief Obtiene las dimensiones. Tipo glm::vec2
    */
    glm::vec2 getSize() const { return size; }
};
#endif