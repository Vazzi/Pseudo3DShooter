#include "Gun.hpp"

#include "../InputHandler.hpp"
#include "../managers/SoundManager.hpp"

Gun::Gun() : AnimatedObject(){
    m_isShooting = false;
    m_isAnimating = false;
}

void Gun::update(unsigned int deltaTime) {
    if (m_isShooting && m_currentFrame == m_numFrames - 1) {
        // Shooting and last frame > stop shooting
        m_currentRow = 0;
        m_currentFrame = 0;
        m_isAnimating = false;
        m_isShooting = false;
    } else if (!m_isShooting &&
            TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
        // Not shooting and space > start shooting
        TheSoundManager::Instance()->playSound("shot", 0);
        m_isAnimating = true;
        m_currentRow = 1;
        m_currentFrame = 0;
        m_isShooting = true;
    } else if (!m_isShooting &&
            (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
            TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))) {
        // Moving and not shooting > moving
        m_isAnimating = true;
        if (m_isShooting == 0) {
            m_currentRow = 0;
        }
    } else if (m_isShooting) {
        // Is still shooting continue animation
        m_isAnimating = true;
    } else {
        // No animation
        m_isAnimating = false;
        m_currentFrame = 0;
    }
    AnimatedObject::update(deltaTime);
}
