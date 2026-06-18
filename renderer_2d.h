#pragma once
#ifndef RENDERER_2D_CLASS_H
#define RENDERER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_class.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

class Sprite;

class Renderer2D
{
	public:
		Shader shader;
		Renderer2D();

		void draw(const Sprite& sprite, const glm::mat4& projection) const;
	private:
		GLuint VAO_id;
};

#endif