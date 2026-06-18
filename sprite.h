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

    glm::ivec2 frameIndex;
    glm::vec2 frameOffset;
    glm::vec2 frameSize;
    glm::vec2 frameGap;

    Sprite(
        const Texture& _texture, 
        const glm::vec2& _position,
        const glm::vec2& _size,
        const glm::ivec2& _frameIndex,
        const glm::vec2& _frameOffset,
        const glm::vec2& _frameSize,
        const glm::vec2& _frameGap
    );

    void setPosition(const glm::vec2 _position);
    glm::vec2 getUVOffset() const;
};

#endif