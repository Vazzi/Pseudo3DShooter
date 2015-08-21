#include "World.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "../InputHandler.hpp"
#include "../managers/BitmapManager.hpp"
#include "../json/WorldParser.hpp"
#include "../managers/CollisionManager.hpp"

World::World() : m_position(Vector2D(0, 0)) {
    // empty
}

void World::render() {
    m_pRayCast->drawWorld();
    m_pRayCast->render(m_position.getX(), m_position.getY(), m_width, m_height);
}

void World::update(unsigned int deltaTime) {
    movePlayer();
    ThePlayer::Instance()->update(deltaTime);
}

void World::movePlayer() {
    double posX = ThePlayer::Instance()->getPosition().getX();
    double posY = ThePlayer::Instance()->getPosition().getY();

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        double nextStepX = ThePlayer::Instance()->nextStepX(false);
        if (m_pMap->isEmpty(nextStepX, posY) &&
                !CollisionManager::collide(nextStepX, posY, m_sprites)) {
            ThePlayer::Instance()->moveSteps(1,0);
        }
        double nextStepY = ThePlayer::Instance()->nextStepY(false);
        if(m_pMap->isEmpty(posX, nextStepY) &&
                !CollisionManager::collide(posX, nextStepY, m_sprites)) {
            ThePlayer::Instance()->moveSteps(0,1);
        }
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        double nextStepX = ThePlayer::Instance()->nextStepX(true);
        if (m_pMap->isEmpty(nextStepX, posY) &&
                !CollisionManager::collide(nextStepX, posY, m_sprites)) {
            ThePlayer::Instance()->moveSteps(-1,0);
        }
        double nextStepY = ThePlayer::Instance()->nextStepY(true);
        if(m_pMap->isEmpty(posX, nextStepY) &&
                !CollisionManager::collide(posX, nextStepY, m_sprites)) {
            ThePlayer::Instance()->moveSteps(0,-1);
        }
    }
}

void World::clean() {
    ThePlayer::Instance()->clean();
    delete m_pMap;

    for (unsigned long i = 0; i < m_sprites.size(); i++) {
        m_sprites[i]->clean();
    }
    for (unsigned long i = 0; i < m_textureIDs.size(); i++) {
        TheBitmapManager::Instance()->clearFromBitmapMap(m_textureIDs[i]);
    }
    m_sprites.clear();
    m_textureIDs.clear();

}

void World::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_height = pParams->getHeight();
    m_width = pParams->getWidth();
}

void World::loadLevelData(std::string fileName) {
    WorldParser parser;
    parser.parseWorld(fileName.c_str(), &m_sprites, &m_pMap, &m_textureIDs);
    m_pRayCast = new RayCast(m_pMap, &m_sprites);

    m_pRayCast->setSurface(m_width, m_height, 0.5);
}

