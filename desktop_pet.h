#pragma once
#ifndef DESKTOP_PET_CLASS_H
#define DESKTOP_PET_CLASS_H

#include <memory>

#include "character.h"

class Sprite;
class CollisionBox;

/**
* @brief Clase de mascota de escritorio
*/
class DesktopPet : public Character
{
private:

public:
	/**
	 * @brief Constructor de DesktopPet
	 */
	DesktopPet(std::shared_ptr<Sprite> _sprite, std::shared_ptr<CollisionBox> _collider) :
	Character(_sprite, _collider)
	{};
};

#endif