#include "AnimatedObject.hpp"

#include "../managers/TextureManager.hpp"
#include "../Game.hpp"

AnimatedObject::AnimatedObject() : GameObject(), m_position(Vector2D(0,0)) {
    m_currentRow = m_currentFrame = m_numFrames = 0;
}

void AnimatedObject::render() {
    TheTextureManager::Instance()->draw(m_textureID, m_position, m_width, m_height,
           TheGame::Instance()->getRenderer(), m_scale, m_currentFrame, m_currentRow);
}

void AnimatedObject::update(unsigned int deltaTime) {
    // empty
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
