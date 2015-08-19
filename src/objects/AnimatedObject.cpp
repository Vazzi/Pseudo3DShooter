#include "AnimatedObject.hpp"

#include "../managers/TextureManager.hpp"
#include "../InputHandler.hpp"
#include "../Game.hpp"

AnimatedObject::AnimatedObject() : GameObject(), m_position(Vector2D(0,0)) {
    m_currentRow = m_currentFrame = m_numFrames = 0;
    m_animTime = 0;
    m_animSpeed = 20;
}

void AnimatedObject::render() {
    TheTextureManager::Instance()->draw(m_textureID, m_position, m_width, m_height,
           TheGame::Instance()->getRenderer(), m_scale, m_currentFrame, m_currentRow);
}

void AnimatedObject::update(unsigned int deltaTime) {

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
            TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        if (m_animTime <= 0 ) {
            m_currentFrame = (m_currentFrame + 1) % m_numFrames;
            m_animTime = m_animSpeed;
        } else {
            m_animTime--;
        }
    } else {
        m_currentFrame = 0;
    }
}

void AnimatedObject::clean() {
    // empty
}

void AnimatedObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
    m_scale = pParams->getScale();
}
