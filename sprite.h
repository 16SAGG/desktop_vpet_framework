#pragma once
#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <optional>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "renderer_2d.h"
#include "texture.h"

class Renderer2D;

/**
* @brief El sprite es un contenedor con la informacion de como debe comportarse una textura en pantalla.
* Construye un sprite a partir de la referencia de una textura compartida.
*/
class Sprite
{
private:
    //Referencia a la textura del sprite. Tipo std::shared_ptr<Texture>
    std::shared_ptr<Texture> texture;

    //Es la posicion donde se va a dibujar la textura. Tipo glm::vec2
    glm::vec2 position = { 0,0 };
    //Es el tamaño que tendra la textura. Tipo glm::vec2
    glm::vec2 size = { 0,0 };

    //Indica los indices de los frames vec2(indice_horizontal, indice_vertical). Tipo glm::vec2
    glm::ivec2 frameIndex = { 0,0 };
    //Indica la posicion donde se iniciara el corte del frame (posicion superior-izquierda), la unidad de los valores es "pixeles". Tipo glm::vec2
    glm::vec2 frameOffset = { 0,0 };
    //Determina tamaño del corte del frame, la unidad de los valores es "pixeles". Tipo glm::vec2
    glm::vec2 frameSize = { 0,0 };
    //Representa el espaciado que hay entre los frames del atlas, la unidad de los valores es "pixeles". Tipo glm::vec2
    glm::vec2 frameGap = { 0,0 };
public:
    //METHODS

    /**
     * @brief Constructor de Sprite
     * * @example
     * //Ejemplo de definicion:
     * auto textureShared = std::make_shared<Texture>("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
     * textureShared -> texUnit(renderer.shader, "tex0", 0);
     *
     * Sprite sprite(textureShared, renderer);
     * * @param _texture La referencia a la textura. Tipo std::shared_ptr<Texture>
     *  @param _renderer Objeto renderer donde se dibujara este sprite. Tipo Renderer
     */
    Sprite(const std::shared_ptr<Texture> _texture);

    /**
     * @brief El sprite es un contenedor con la informacion de como debe comportarse una textura en pantalla.
     * Construye un sprite a partir de la ruta a una textura.
     * * @example
     * //Ejemplo de definicion:
     * Sprite sprite2 = Sprite::CreateFromPath("texture_2", renderer);
     * * @param path Ruta al archivo. Tipo char*
     *  @param _renderer Objeto renderer donde se dibujara este sprite. Tipo Renderer
     */
    static Sprite createFromPath(const char* path, Renderer2D& renderer);

    //SETTERS

    /**
     * @brief Cambia el valor de variable position del sprite
     * * @param _position Es la posicion donde se va a dibujar el sprite. Tipo glm::vec2
     */
    void setPosition(const glm::vec2& _position) { position = _position; }

    /**
     * @brief Cambia el valor de variable size del sprite
     * * @param _size Es el tamaño que tendra la textura. Tipo glm::vec2
     */
    void setSize(const glm::vec2& _size) { size = _size; }

    /**
     * @brief Cambia el valor de variable frameIndex del sprite
     * * @param _frameIndex Indica los indices de los frames vec2(indice_horizontal, indice_vertical). Tipo glm::vec2
     */
    void setFrameIndex(const glm::vec2& _frameIndex) { frameIndex = _frameIndex; }

    /**
     * @brief Cambia el valor de variable frameOffset del sprite
     * * @param _frameOffset Indica la posicion donde se iniciara el corte del frame (posicion superior-izquierda), la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    void setFrameOffset(const glm::vec2& _frameOffset) { frameOffset = _frameOffset; }

    /**
     * @brief Cambia el valor de variable frameSize del sprite
     * * @param _frameSize Determina tamaño del corte del frame, la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    void setFrameSize(const glm::vec2& _frameSize) { frameSize = _frameSize; }

    /**
     * @brief Cambia el valor de variable frameGap del sprite
     * * @param _frameGap Representa el espaciado que hay entre los frames del atlas, la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    void setFrameGap(const glm::vec2& _frameGap) { frameGap = _frameGap; }

    //GETTERS

    /**
     * @brief obtiene la referencia a la textura del sprite.Tipo std::shared_ptr<Texture>
     */
    std::shared_ptr<Texture> getTexture() const { return texture; }

    /**
     * @brief obtiene la posicion donde se va a dibujar la textura. Tipo glm::vec2
     */
    glm::vec2 getPosition() const { return position; }

    /**
     * @brief obtiene el tamaño que tendra la textura. Tipo glm::vec2
     */
    glm::vec2 getSize() const { return size; }

    /**
     * @brief obtiene los indices de los frames vec2(indice_horizontal, indice_vertical). Tipo glm::ivec2
     */
    glm::ivec2 getFrameIndex() const { return frameIndex; }
    
    /**
     * @brief obtiene la posicion donde se iniciara el corte del frame (posicion superior-izquierda), la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    glm::vec2 getFrameOffset() const { return frameOffset; }
    
    /**
     * @brief obtiene el tamaño del corte del frame, la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    glm::vec2 getFrameSize() const { return frameSize; }
    
    /**
     * @brief obtiene el espaciado que hay entre los frames del atlas, la unidad de los valores es "pixeles". Tipo glm::vec2
     */
    glm::vec2 getFrameGap() const { return frameGap;  }

    /**
     * @brief Calcula y obtiene el UVOffset del sprite. Tipo glm::vec2
     */
    glm::vec2 getUVOffset() const;
};

#endif