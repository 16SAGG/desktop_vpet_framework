#include "glm/fwd.hpp"
#include <glm/glm.hpp>

#include "utils.h"

Utils& Utils::getInstance() {
    static Utils instance;
    return instance;
}

glm::vec2 Utils::getNormalizedDirection(glm::vec2 origin, glm::vec2 target) {
    glm::vec2 direction = target - origin;

    float distance = glm::length(direction);

    if (distance > 0.0001f) {
        return glm::normalize(direction);
    }

    return glm::vec2(0.0f, 0.0f);
}