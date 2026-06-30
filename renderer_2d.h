#pragma once
#ifndef RENDERER_2D_CLASS_H
#define RENDERER_CLASS_H

#include <memory>
#include <glad/glad.h>
#include "glm/fwd.hpp"

#include "shader.h"
#include "entity.h"

class Sprite;

/**
 * @brief Es el motor de dibujo del sistema.
 * * Este proceso carga el programa de shaders y prepara el VAO, VBO y EBO
 * con los datos necesarios para dibujar un cuadrado texturizado.
 */
class Renderer2D
{
	private:
		//Referencia al shader que se construye para el renderer. Tipo Shader
		Shader shader;

		/**
		 * @brief Constructor del Renderer2D
		 */
		Renderer2D();
	public:
		/**
		* @brief Obtiene la unica instancia de Renderer2D
		*/
		static Renderer2D& getInstance();

		/**
		 * @brief Renderiza un objeto 2D con una textura y transformación específica.
		 * * Utiliza matrices para posicionar y escalar el objeto en el mundo virtual,
		 * y envía estos datos al shader para su procesamiento final.
		 * * @param sprite Objeto sprite que se aplicará sobre la geometría. Tipo Sprite&
		 * @param projection Matriz 4x4 de proyección que define cómo se mapean las coordenadas
		 * del mundo a la pantalla (útil para manejar la relación de aspecto). Tipo glm::mat4&
		 */
		void draw(const std::shared_ptr<Sprite> sprite, const glm::mat4& projection) const;

		/**
		 * @brief Aplica color sobre una entidad. Util para ver entidades invisibles cuando se hace debug.
		 * * Utiliza matrices para posicionar y escalar el objeto en el mundo virtual,
		 * y envía estos datos al shader para su procesamiento final.
		 * * @param sprite Objeto sprite que se aplicará sobre la geometría. Tipo Sprite&
		 * @param projection Matriz 4x4 de proyección que define cómo se mapean las coordenadas
		 * del mundo a la pantalla (útil para manejar la relación de aspecto). Tipo glm::mat4&
		 */
		void drawColoredEntity(const std::shared_ptr<Entity> entity, const glm::mat4& projection, const glm::vec4 color) const;

		//GETTER

		/**
		 * @brief Obtiene el valor shader. Tipo Shader
		 */
		const Shader& getShader() const { return shader; };
		
		//SETTER

		/**
		 * @brief Establece el valor shader
		 */
		void setShader(Shader _shader) { shader = _shader; };
	private:
		// ID del VAO vinculado al renderer
		GLuint VAO_id;
};

#endif