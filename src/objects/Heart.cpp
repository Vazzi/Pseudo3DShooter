#include "Heart.hpp"
#include "Player.hpp"

void Heart::update(unsigned int deltaTime) {
    int health = ThePlayer::Instance()->getHealth();
    if (health > 70) {
        m_currentRow = 0;
    } else if (health > 30) {
        m_currentRow = 1;
    } else {
        m_currentRow = 2;
    }

    AnimatedObject::update(deltaTime);
}
