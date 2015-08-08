#include "World.hpp"
#include "../Game.hpp"
#include "../InputHandler.hpp"
#include "../SurfaceManager.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "../states/StateParser.hpp"
#include "../utility/GameSurface.hpp"
#include "../utility/Ray.hpp"

World::World() : m_position(Vector2D(0, 0)) {
    // empty
}

void World::render() {
    drawWalls();
    renderSurface();
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
    delete m_pGameSurface;
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
    m_time = 0;
    m_oldTime = 0;
    float scale = 1;
    m_pGameSurface = new GameSurface(m_width * scale, m_height * scale);
}

void World::loadLevelData(std::string fileName) {
    StateParser parser;
    parser.parseWorld(fileName.c_str(), &m_gameObjects, &m_pMap, &m_pPlayer,
            &m_textureIDs);
    m_pGameSurface->setFormatBySurface(
            TheSurfaceManager::Instance()->getSurface(m_textureIDs[0]));
}

void World::renderSurface() {
    m_pGameSurface->draw(m_position.getX(), m_position.getY(), m_width, m_height);
    m_pGameSurface->clear();
}

void World::drawWalls() {
    SDL_Surface* pCeiling = TheSurfaceManager::Instance()->getSurface(
                    m_pMap->getCeilingTextureID());
    SDL_Surface* pFloor = TheSurfaceManager::Instance()->getSurface(
                    m_pMap->getFloorTextureID());

    for (int x = 0; x < m_pGameSurface->getWidth(); x++) {
        Ray ray = Ray(x, m_pGameSurface->getWidth(), m_pPlayer);
        ray.performDDA(m_pMap);

        // Calculate height of line to draw on screen
        int lineHeight = abs(int(m_pGameSurface->getHeight() / ray.getWallDist()));

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + m_pGameSurface->getHeight() / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + m_pGameSurface->getHeight() / 2;
        if (drawEnd >= m_pGameSurface->getHeight()) {
            drawEnd = m_pGameSurface->getHeight() - 1;
        }

        double wallX = ray.getWallX();

        // Get texture calculations
        std::string textureID = m_pMap->getWallTextureID(ray.getMapX(), ray.getMapY());
        SDL_Surface* pTexture = TheSurfaceManager::Instance()->getSurface(textureID);

        //x coordinate on the texture
        int texX = int(wallX * double(pTexture->w));
        if (ray.getSide() == 0 && ray.getDirX() > 0) {
            texX = pTexture->w - texX - 1;
        }
        if (ray.getSide() == 1 && ray.getDirY() < 0) {
            texX = pTexture->w - texX - 1;
        }
        for (int y = drawStart; y < drawEnd; y++) {
            //256 and 128 factors to avoid floats
            int d = y * 256 - m_pGameSurface->getHeight() * 128 + lineHeight * 128;
            int texY = ((d * pTexture->h) / lineHeight) / 256;
            Uint32 color = GameSurface::getPixelFromSurface(pTexture, texX, texY);
            m_pGameSurface->putPixel(x, y, color);
        }

        // FLOOR CASTING
        double floorXWall, floorYWall;

        // 4 different wall directions possible
        if(ray.getSide() == 0 && ray.getDirX() > 0) {
            floorXWall = ray.getMapX();
            floorYWall = ray.getMapY() + wallX;
        } else if(ray.getSide() == 0 && ray.getDirX() < 0) {
            floorXWall = ray.getMapX() + 1.0;
            floorYWall = ray.getMapY() + wallX;
        } else if(ray.getSide() == 1 && ray.getDirY() > 0) {
            floorXWall = ray.getMapX() + wallX;
            floorYWall = ray.getMapY();
        } else {
            floorXWall = ray.getMapX() + wallX;
            floorYWall = ray.getMapY() + 1.0;
        }

        double distWall, distPlayer, currentDist;

        distWall = ray.getWallDist();
        distPlayer = 0.0;

        if (drawEnd < 0) {
            drawEnd = m_pGameSurface->getHeight(); //becomes < 0 when the integer overflows
        }

        for(int y = drawEnd + 1; y < m_pGameSurface->getHeight(); y++) {
            currentDist = m_pGameSurface->getHeight() / (2.0 * y - m_pGameSurface->getHeight());

            double weight = (currentDist - distPlayer) / (distWall - distPlayer);

            double currentFloorX = weight * floorXWall + (1.0 - weight) * m_pPlayer->getPosition().getX();
            double currentFloorY = weight * floorYWall + (1.0 - weight) * m_pPlayer->getPosition().getY();

            int floorTexX, floorTexY;
            floorTexX = int(currentFloorX * pFloor->w) % pFloor->w;
            floorTexY = int(currentFloorY * pFloor->h) % pFloor->h;

            Uint32 color = GameSurface::getPixelFromSurface(pFloor, floorTexX, floorTexY);
            color = (color >> 1) & 8355711;
            m_pGameSurface->putPixel(x, y, color);

            color = GameSurface::getPixelFromSurface(pCeiling, floorTexX, floorTexY);
            color = (color >> 1) & 8355711;
            m_pGameSurface->putPixel(x, m_height-y, color);
        }
    }

}

