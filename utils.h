#pragma once
#ifndef UTILS_CLASS_H
#define UTILS_CLASS_H

#include "glm/fwd.hpp"
#include <glm/glm.hpp>

class Utils
{
private:
	/**
	 * @brief Constructor de Utils.
	 */
	Utils() {};
public:
	/**
	* @brief Obtiene la unica instancia de Utils
	*/
	static Utils& getInstance();

	/**
	* @brief Obtiene la direccion normalizada entre dos vectores. Tipo glm::vec2
	* @param origin El primer vector. Tipo glm::vec2
	* @param target El segundo vector. Tipo glm::vec2
	*/
	glm::vec2 getNormalizedDirection(glm::vec2 origin, glm::vec2 target);
};

#endif