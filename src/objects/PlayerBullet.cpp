#include "PlayerBullet.hpp"

PlayerBullet::PlayerBullet() : Sprite(), m_heading(Vector2D(0,0)) {
    // empty
}

void PlayerBullet::load(LoaderParams* pParams, Vector2D heading) {
    Sprite::load(pParams);
    m_heading = heading;
}

void PlayerBullet::render() {
    Sprite::render();
}

void PlayerBullet::update(unsigned int deltaTime) {
    m_position += m_heading;
    Sprite::update(deltaTime);
}

void PlayerBullet::clean() {
    Sprite::clean();
}

