#include "BulletHandler.hpp"

#include "../objects/PlayerBullet.hpp"

BulletHandler* BulletHandler::s_pInstance = 0;

BulletHandler::BulletHandler() {

}

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, 
        string textureID, int numFrames, Vector2D heading) {
    PlayerBullet* pPlayerBullet = new PlayerBullet();
    pPlayerBullet->load(new LoaderParams(x, y, width, height, textureID, 0, 1,
                numFrames), heading);

    m_playerBullets.push(pPlayerBullet);
}

void BulletHandler::update(unsigned int deltaTime) {
    for (unsigned long i = 0; i < m_playerBullets.size(); i++) {
        m_playerBullets[i]->update(deltaTime);
    }
}

void BulletHandler::render() {
    for (unsigned long i = 0; i < m_playerBullets.size(); i++) {
        m_playerBullets[i]->redner();
    }
}
