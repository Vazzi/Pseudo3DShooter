#include "RayCast.hpp"
#include "../objects/Map.hpp"
#include "../objects/Player.hpp"
#include "../objects/GameObject.hpp"
#include "../SurfaceManager.hpp"
#include "../utility/GameSurface.hpp"

RayCast::RayCast(Map *pMap, Player* pPlayer, vector<GameObject*>* pGameObjects) {
    m_pMap = pMap;
    m_pPlayer = pPlayer;
    m_pGameObjects = pGameObjects;
    m_pFloorTexture = TheSurfaceManager::Instance()->getSurface(
            pMap->getFloorTextureID());
    m_pCeilingTexture = TheSurfaceManager::Instance()->getSurface(
            pMap->getCeilingTextureID());
}

RayCast::~RayCast() {
    m_pMap = NULL;
    m_pPlayer = NULL;
    m_pGameObjects = NULL;
    m_pFloorTexture = NULL;
    m_pCeilingTexture = NULL;
    delete m_pGameSurface;
}

void RayCast::setSurface(int width, int height, int scale) {
    m_pGameSurface = new GameSurface(width * scale, height * scale);
    m_pGameSurface->setFormatBySurface(m_pCeilingTexture);
}

void RayCast::render(int x, int y, int width, int height) {
    m_pGameSurface->draw(x, y, width, height);
    m_pGameSurface->clear();
}

void RayCast::drawWorld() {
    for (int x = 0; x < m_pGameSurface->getWidth(); x++) {
        Ray ray = Ray(x, m_pGameSurface->getWidth(), m_pPlayer);
        ray.performDDA(m_pMap);
        drawWalls(x, ray);
        drawFloorAndCeiling(x, ray);
        drawSprites(x, ray);
    }
}

void RayCast::drawWalls(int x, Ray &ray) {

    // Calculate height of line to draw on screen
    int lineHeight = abs(int(m_pGameSurface->getHeight() / ray.getWallDist()));

    // Calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + m_pGameSurface->getHeight() / 2;
    if (drawStart < 0) {
        drawStart = 0;
    }
    m_drawEnd = lineHeight / 2 + m_pGameSurface->getHeight() / 2;
    if (m_drawEnd >= m_pGameSurface->getHeight()) {
        m_drawEnd = m_pGameSurface->getHeight() - 1;
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

    for (int y = drawStart; y < m_drawEnd; y++) {
        //256 and 128 factors to avoid floats
        int d = y * 256 - m_pGameSurface->getHeight() * 128 + lineHeight * 128;
        int texY = ((d * pTexture->h) / lineHeight) / 256;
        Uint32 color = GameSurface::getPixelFromSurface(pTexture, texX, texY);
        m_pGameSurface->putPixel(x, y, color);
    }
}

void RayCast::drawFloorAndCeiling(int x, Ray &ray) {

    double floorXWall, floorYWall;
    double wallX = ray.getWallX();

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

    if (m_drawEnd < 0) {
        m_drawEnd = m_pGameSurface->getHeight(); //becomes < 0 when the integer overflows
    }

    for(int y = m_drawEnd + 1; y < m_pGameSurface->getHeight(); y++) {
        currentDist = m_pGameSurface->getHeight() / (2.0 * y - m_pGameSurface->getHeight());

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * m_pPlayer->getPosition().getX();
        double currentFloorY = weight * floorYWall + (1.0 - weight) * m_pPlayer->getPosition().getY();

        int floorTexX, floorTexY;
        floorTexX = int(currentFloorX * m_pFloorTexture->w) % m_pFloorTexture->w;
        floorTexY = int(currentFloorY * m_pFloorTexture->h) % m_pFloorTexture->h;

        Uint32 color = GameSurface::getPixelFromSurface(m_pFloorTexture, floorTexX, floorTexY);
        color = (color >> 1) & 8355711;
        m_pGameSurface->putPixel(x, y, color);

        color = GameSurface::getPixelFromSurface(m_pCeilingTexture, floorTexX, floorTexY);
        color = (color >> 1) & 8355711;
        m_pGameSurface->putPixel(x, m_pGameSurface->getHeight() - y, color);
    }
}

void RayCast::drawSprites(int x, Ray &ray) {

}
