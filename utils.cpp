#include <glm/glm.hpp>
#include <windows.h>
#include <random>
#include <cmath>

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

glm::vec2 Utils::getScreenSize() {
    RECT workArea{};
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

    return { workArea.right - workArea.left, workArea.bottom - workArea.top };
}

float Utils::getRandomNumber(const float limit1, const float limit2) {
    std::uniform_real_distribution<float> distX(limit1, limit2);
    return distX(getGenerator());
}

glm::vec2 Utils::getRandomVector(const glm::vec2& vector1, const glm::vec2& vector2) {
    return glm::vec2(this->getRandomNumber(vector1.x, vector2.x), this->getRandomNumber(vector1.y, vector2.y));
}

glm::vec2 Utils::convertToIntVector(const glm::vec2 vector) {
    return glm::vec2(static_cast<int>(vector.x), static_cast<int>(vector.y));
}

glm::vec2 Utils::getRoundedNormal(glm::vec2 vector) {
    float roundedX = std::round(vector.x);
    float roundedY = std::round(vector.y);

    roundedX = std::clamp(roundedX, -1.0f, 1.0f);
    roundedY = std::clamp(roundedY, -1.0f, 1.0f);

    return glm::vec2(roundedX, roundedY);
}