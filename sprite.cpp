#include "sprite.h"

/**
 * @brief El sprite es un contenedor con la informacion de como debe comportarse una textura en pantalla.
 * * @param _texture La referencia a la textura. Tipo Texture
 * * @param _position Es la posicion relativa a su dueño donde se va a dibujar el sprite. Tipo glm::vec2
 * * @param _size Es el tamaño que tendra la textura. Tipo glm::vec2
 * * @param _frameIndex Indica los indices de los frames vec2(indice_horizontal, indice_vertical). Tipo glm::vec2
 * * @param _frameOffset Indica la posicion donde se iniciara el corte del frame (posicion superior-izquierda), la unidad de los valores es "pixeles". Tipo glm::vec2
 * * @param _frameSize Determina tamaño del corte del frame, la unidad de los valores es "pixeles". Tipo glm::vec2
 * * @param _frameGap Representa el espaciado que hay entre los frames del atlas, la unidad de los valores es "pixeles". Tipo glm::vec2
 */
Sprite :: Sprite(
    const Texture& _texture,
    const glm::vec2& _position,
    const glm::vec2& _size,
    const glm::ivec2& _frameIndex,
    const glm::vec2& _frameOffset,
    const glm::vec2& _frameSize,
    const glm::vec2& _frameGap
):
	texture (_texture),
	position(_position), 
	size(_size), 
	frameIndex(_frameIndex), 
	frameOffset(_frameOffset),
    frameSize(_frameSize),
    frameGap(_frameGap)
{

}

/**
 * @brief Cambia el valor de variable position del sprite
 * * @param _position Nuevo valor de la variable position. Tipo glm::vec2 _position
 */
void Sprite::setPosition(const glm::vec2 _position) {
    position = _position;
}

/**
 * @brief Calcula y obtiene el UVOffset del sprite
 */
glm::vec2 Sprite::getUVOffset() const {
    return frameOffset + (glm::vec2(frameIndex) * (frameSize + frameGap));
}