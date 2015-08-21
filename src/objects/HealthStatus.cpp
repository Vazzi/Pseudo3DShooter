#include "HealthStatus.hpp"

#include <string>
#include "Player.hpp"

void HealthStatus::update(unsigned int deltaTime) {
    int health = ThePlayer::Instance()->getHealth();
    std::string text = std::to_string(health);
    setText(text);
    TextObject::update(deltaTime);
}

