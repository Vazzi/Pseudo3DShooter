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
    // empty
}

void Sprite::update(unsigned int deltaTime) {
    // empty
}

void Sprite::clean() {
    // empty
}

void Sprite::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_textureID = pParams->getTextureID();
}

