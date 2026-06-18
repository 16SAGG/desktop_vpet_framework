#pragma once
#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"

class Sprite
{
public:
    Texture texture;

    glm::vec2 position;
    glm::vec2 size;

    glm::vec2 uvOffset;
    glm::vec2 uvScale;

    Sprite(const Texture& _texture, const glm::vec2 _position, const glm::vec2 _size, const glm::vec2 _uvOffset, const glm::vec2 _uvScale);

    void setPosition(const glm::vec2 _position);
};

#endif