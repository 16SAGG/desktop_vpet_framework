#pragma once
#ifndef UTILS_CLASS_H
#define UTILS_CLASS_H

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <random>

class Utils
{
private:
	/**
	 * @brief Constructor de Utils.
	 */
	Utils() {};

	/*
	* @brief Obtiene un generador para numero aleatorio
	*/
	static std::mt19937& getGenerator() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return gen;
	}
public:
	/**
	* @brief Obtiene la unica instancia de Utils
	*/
	static Utils& getInstance();

	//GETTERS
	/**
	* @brief Obtiene la direccion normalizada entre dos vectores. Tipo glm::vec2
	* @param origin El primer vector. Tipo glm::vec2
	* @param target El segundo vector. Tipo glm::vec2
	*/
	glm::vec2 getNormalizedDirection(glm::vec2 origin, glm::vec2 target);

	/*
	* @brief Obtiene el tamano de la pantalla. Tipo glm::vec2
	*/
	glm::vec2 getScreenSize();

	/*
	* @brief Obtiene un numero aleatorio entre dos numeros. Tipo float
	* @param limit1 El primer numero limite. Tipo float
	* @param limit2 El segundo numero limite. Tipo float
	*/
	float getRandomNumber(const float limit1, const float limit2);

	/*
	* @brief Obtiene un vector aleatorio entre dos vectores. Tipo glm::vec2
	* @param vectorLimit1 El primer vector limite. Tipo glm::vec2
	* @param vectorLimit2 El segundo vector limite. Tipo glm::vec2
	*/
	glm::vec2 getRandomVector(const glm::vec2& vector1, const glm::vec2& vector2);

	/*
	* @brief Convierte un vector flotante en un vector entero. Tipo glm::vec2
	* @param vector El vector a convertir. Tipo glm::vec2
	*/
	glm::vec2 convertToIntVector(const glm::vec2 vector);

	/*
	* @brief Convierte un vector cualquiera en un vector redondeado normal (Ej: (0, -1); (1, 0)). Tipo glm::vec2
	* @param vector El vector a convertir. Tipo glm::vec2
	*/
	glm::vec2 getRoundedNormal(glm::vec2 vector);
};

#endif