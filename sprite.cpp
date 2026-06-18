#include "sprite.h"

/**
 * @brief El sprite es un contenedor con la informacion de como debe comportarse una textura en pantalla.
 * * @param _texture La referencia a la textura. Tipo Texture
 * * @param _position Es la posicion relativa a su dueño donde se va a dibujar el sprite. Tipo glm::vec2
 * * @param _size Es el tamaño que tendra la textura. Tipo glm::vec2
 * * @param _uvOffset Define el punto (superior izquierdo) donde se empezara a cortar el atlas de la textura, en caso de no usar un atlas deja como (0,0). Tipo glm::vec2
 * * @param _uvScale Define el tamaño del cuadrado que se va a recortar del atlas, en caso de no usar un atlas deja como (1,1). Tipo glm::vec2
 */
Sprite :: Sprite(const Texture& _texture, const glm::vec2 _position, const glm::vec2 _size, const glm::vec2 _uvOffset, const glm::vec2 _uvScale) : 
	texture (_texture),
	position(_position), 
	size(_size), 
	uvOffset(_uvOffset), 
	uvScale(_uvScale)
{

}

/**
 * @brief Cambia el valor de variable position del sprite
 * * @param _position Nuevo valor de la variable position. Tipo glm::vec2 _position
 */
void Sprite :: setPosition(const glm::vec2 _position) {
	position = _position;
}