#pragma once
#ifndef PROCESS_CLASS_H
#define PROCESS_CLASS_H

#include <functional>
#include <GLFW/glfw3.h>

/**
 * @brief Gestiona el ciclo de vida de ejecución del motor.
 * * La clase Proccess encapsula el bucle principal de la aplicación, controlando
 * la sincronización entre frames mediante el cálculo de 'deltaTime'.
 */
class Process
{
private:
	// Referencia a la ventana que encapsula este objeto.
	GLFWwindow* window;
	//Guarda temporalmente el frame anterior para compararlo con el nuevo y asi calcular el deltaTime
	float lastFrame;
public:
	/**
	 * @brief Callback de actualización por frame.
	 * @param deltaTime Tiempo transcurrido en segundos desde el último frame.
	 */
	using UpdateCallback = std::function<void(float)>;
	
	/**
	 * @brief Constructor de Process.
	 * @param window Puntero a la ventana de GLFW que controla el bucle. Tipo GLFWwindow*
	 */
	Process(GLFWwindow* window);

	/**
	 * @brief Ejecuta el bucle principal de la aplicación.
	 * * Mantiene la ventana abierta, calcula el deltaTime automáticamente y ejecuta
	 * la función de actualización (updateFunc) en cada iteración del bucle.
	 * * @param updateFunc Función a ejecutar por frame (recibe el deltaTime). Tipo UpdateCallback
	 */
	void run(UpdateCallback updateFunc);
};

#endif