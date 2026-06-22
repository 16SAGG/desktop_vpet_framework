#include "sprite.h"

Sprite :: Sprite(const std::shared_ptr<Texture> _texture):
	texture (_texture)
{
    size = glm::vec2((float)_texture -> getWidthImg(), (float)_texture -> getHeightImg());
    frameSize = glm::vec2((float)_texture->getWidthImg(), (float)_texture->getHeightImg());
}

std::shared_ptr<Sprite> Sprite::createFromPath(const char* path, Renderer2D& _renderer) {
    auto texturePtr = std::make_shared<Texture>(path, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texturePtr -> texUnit(_renderer.shader, "tex0", 0);

    return std::make_shared<Sprite>(texturePtr);
}

glm::vec2 Sprite::getUVOffset() const {
    return frameOffset + (glm::vec2(frameIndex) * (frameSize + frameGap));
}