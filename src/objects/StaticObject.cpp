#include "StaticObject.hpp"
#include "../TextureManager.hpp"
#include "../Game.hpp"

StaticObject::StaticObject() : m_position(Vector2D(0, 0)) {
    // empty
}

StaticObject::~StaticObject() {
    // empty
}

void StaticObject::render() {
    TheTextureManager::Instance()->draw(m_textureID, m_position.getX(),
            m_position.getY(), m_width, m_height,
            TheGame::Instance()->getRenderer());
}

void StaticObject::update(unsigned int deltaTime) {
    // empty
}

void StaticObject::clean() {
    // empty
}

void StaticObject::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
}

