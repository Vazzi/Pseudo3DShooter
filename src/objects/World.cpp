#include "World.hpp"
#include "../InputHandler.hpp"
#include "../SurfaceManager.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "../json/StateParser.hpp"

World::World() : m_position(Vector2D(0, 0)) {
    // empty
}

void World::render() {
    m_pRayCast->drawWorld();
    m_pRayCast->render(m_position.getX(), m_position.getY(), m_width, m_height);
}

void World::update(unsigned int deltaTime) {
    m_pPlayer->update(deltaTime);

    double posX = m_pPlayer->getPosition().getX();
    double posY = m_pPlayer->getPosition().getY();

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        if (m_pMap->isEmpty(m_pPlayer->nextStepX(false), posY)) {
            m_pPlayer->moveSteps(1,0);
        }
        if(m_pMap->isEmpty(posX, m_pPlayer->nextStepY(false))) {
            m_pPlayer->moveSteps(0,1);
        }
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        if (m_pMap->isEmpty(m_pPlayer->nextStepX(true), posY)) {
            m_pPlayer->moveSteps(-1,0);
        }
        if (m_pMap->isEmpty(posX, m_pPlayer->nextStepY(true))) {
            m_pPlayer->moveSteps(0,-1);
        }
    }
}

void World::clean() {
    m_pPlayer->clean();
    delete m_pPlayer;
    delete m_pMap;

    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    for (unsigned long i = 0; i < m_textureIDs.size(); i++) {
        TheSurfaceManager::Instance()->clearFromSurfaceMap(m_textureIDs[i]);
    }
    m_gameObjects.clear();
    m_textureIDs.clear();

}

void World::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_height = pParams->getHeight();
    m_width = pParams->getWidth();
}

void World::loadLevelData(std::string fileName) {
    StateParser parser;
    parser.parseWorld(fileName.c_str(), &m_gameObjects, &m_pMap, &m_pPlayer,
            &m_textureIDs);
    m_pRayCast = new RayCast(m_pMap, m_pPlayer, &m_gameObjects);

    m_pRayCast->setSurface(m_width, m_height, 1);
}

