#include "Sprite.hpp"
#include "../TextureManager.hpp"
#include "../Game.hpp"

Sprite::Sprite() : m_position(Vector2D(0, 0)) {
    // empty
}

Sprite::~Sprite() {
    // empty
}

void Sprite::render() {
    TheTextureManager::Instance()->draw(m_textureID, m_position.getX(),
            m_position.getY(), m_width, m_height,
            TheGame::Instance()->getRenderer());
}

void Sprite::update(unsigned int deltaTime) {
    // empty
}

void Sprite::clean() {
    // empty
}

void Sprite::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
}

