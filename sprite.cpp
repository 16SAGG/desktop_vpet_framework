#include "glad/glad.h"
#include <memory>
#include "glm/ext/vector_float2.hpp"

#include "sprite.h"
#include "texture.h"
#include "renderer_2d.h"

Sprite :: Sprite(const std::shared_ptr<Texture> _texture):
	texture (_texture)
{
    this->size = glm::vec2((float)_texture -> getWidthImg(), (float)_texture -> getHeightImg());
    this->frameSize = glm::vec2((float)_texture->getWidthImg(), (float)_texture->getHeightImg());
}

std::shared_ptr<Sprite> Sprite::createFromPath(const char* path) {
    auto texturePtr = std::make_shared<Texture>(path, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texturePtr -> texUnit(Renderer2D::getInstance().getShader(), "tex0", 0);

    return std::make_shared<Sprite>(texturePtr);
}

glm::vec2 Sprite::getUVOffset() const {
    return this->frameOffset + (glm::vec2(this->frameIndex) * (this->frameSize + this->frameGap));
}