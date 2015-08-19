#include "RayCast.hpp"
#include "../objects/Map.hpp"
#include "../objects/Player.hpp"
#include "../objects/Sprite.hpp"
#include "../objects/Sprite.hpp"
#include "../managers/BitmapManager.hpp"
#include "../utility/GameSurface.hpp"

RayCast::RayCast(Map *pMap, Player* pPlayer, vector<Sprite*>* pSprites) {
    m_pMap = pMap;
    m_pPlayer = pPlayer;
    m_pSprites = pSprites;
    m_pSpriteOrder = new int[pSprites->size()];
    m_pSpriteDistance = new double[pSprites->size()];
}

RayCast::~RayCast() {
    m_pMap = NULL;
    m_pPlayer = NULL;
    m_pSprites = NULL;
    delete m_pGameSurface;
    delete m_pZBuffer;
    delete m_pSpriteOrder;
    delete m_pSpriteDistance;
}

void RayCast::setSurface(int width, int height, float scale) {
    m_pGameSurface = new GameSurface(width * scale, height * scale);

    m_pZBuffer = new double[width];
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
        m_pZBuffer[x] = ray.getWallDist();
        drawFloorAndCeiling(x, ray);
    }
    drawSprites();
}

void RayCast::drawWalls(int x, Ray& ray) {

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
    Uint32* pTexture = TheBitmapManager::Instance()->getBitmap(textureID);
    int texWidth = 64;
    int texHeight= 64;
    //x coordinate on the texture
    int texX = int(wallX * double(texWidth));
    if (ray.getSide() == 0 && ray.getDirX() > 0) {
        texX = texWidth - texX - 1;
    }
    if (ray.getSide() == 1 && ray.getDirY() < 0) {
        texX = texWidth - texX - 1;
    }

    for (int y = drawStart; y < m_drawEnd; y++) {
        //256 and 128 factors to avoid floats
        int d = y * 256 - m_pGameSurface->getHeight() * 128 + lineHeight * 128;
        int texY = ((d * texHeight) / lineHeight) / 256;
        Uint32 color = pTexture[texX + (texY * texHeight)];
        m_pGameSurface->putPixel(x, y, color);
    }

}

void RayCast::drawFloorAndCeiling(int x, Ray& ray) {

    double floorXWall, floorYWall;
    double wallX = ray.getWallX();
    Uint32* pFloorTexture = TheBitmapManager::Instance()
        ->getBitmap(m_pMap->getFloorTextureID());
    Uint32* pCeilingTexture = TheBitmapManager::Instance()
        ->getBitmap(m_pMap->getCeilingTextureID());

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

    int texHeight = 64;
    int texWidth = 64;

    for(int y = m_drawEnd + 1; y < m_pGameSurface->getHeight(); y++) {
        currentDist = m_pGameSurface->getHeight() / (2.0 * y - m_pGameSurface->getHeight());

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * m_pPlayer->getPosition().getX();
        double currentFloorY = weight * floorYWall + (1.0 - weight) * m_pPlayer->getPosition().getY();

        int floorTexX, floorTexY;
        floorTexX = int(currentFloorX * texWidth) % texWidth;
        floorTexY = int(currentFloorY * texHeight) % texHeight;

        Uint32 color = pFloorTexture[floorTexX + (floorTexY * texHeight)];
        color = (color >> 1) & 8355711;
        m_pGameSurface->putPixel(x, y, color);

        color = pCeilingTexture[floorTexX + (floorTexY * texHeight)];
        color = (color >> 1) & 8355711;
        m_pGameSurface->putPixel(x, m_pGameSurface->getHeight() - y, color);
    }
}

void RayCast::drawSprites() {

    int numSprites = int(m_pSprites->size());

    //sort sprites from far to close
    for(int i = 0; i < numSprites; i++) {
        m_pSpriteOrder[i] = i;
        Sprite* pSprite = (Sprite*)(*m_pSprites)[i];
        m_pSpriteDistance[i] = ((m_pPlayer->getPosition().getX() - pSprite->getPosition().getX()) *
                (m_pPlayer->getPosition().getX() - pSprite->getPosition().getX()) +
                (m_pPlayer->getPosition().getY() - pSprite->getPosition().getY()) *
                (m_pPlayer->getPosition().getY() - pSprite->getPosition().getY()));
    }
    combSort(m_pSpriteOrder, m_pSpriteDistance, numSprites);

    //after sorting the sprites, do the projection and draw them
    for (int i = 0; i < numSprites; i++) {
        Sprite* pSprite = (Sprite*)(*m_pSprites)[m_pSpriteOrder[i]];
        std::string textureID = pSprite->getTextureID();
        Uint32* pTexture = TheBitmapManager::Instance()->getBitmap(textureID);
        int texWidth = 64;
        int texHeight = 64;

        //translate sprite position to relative to camera
        double spriteX = pSprite->getPosition().getX() - m_pPlayer->getPosition().getX();
        double spriteY = pSprite->getPosition().getY() - m_pPlayer->getPosition().getY();

        double invDet = 1.0 / (m_pPlayer->getPlaneX() * m_pPlayer->getDirY() -
                m_pPlayer->getDirX() * m_pPlayer->getPlaneY());

        double transformX = invDet * (m_pPlayer->getDirY() * spriteX -
                m_pPlayer->getDirX() * spriteY);
        double transformY = invDet * (-(m_pPlayer->getPlaneY()) * spriteX +
                m_pPlayer->getPlaneX() * spriteY);

        int w = m_pGameSurface->getWidth();
        int h = m_pGameSurface->getHeight();
        int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

        //calculate height of the sprite on screen
        int spriteHeight = abs(int(h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + h / 2;
        if (drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + h / 2;
        if (drawEndY >= h) drawEndY = h - 1;

        //calculate width of the sprite
        int spriteWidth = abs( int (h / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= w) drawEndX = w - 1;


        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) *
                   texWidth / spriteWidth) / 256;
            if (transformY > 0 && stripe > 0 && stripe < w &&
                    transformY < m_pZBuffer[stripe]) {
                for (int y = drawStartY; y < drawEndY; y++) {
                    int d = (y) * 256 - h * 128 + spriteHeight * 128;
                    int texY = ((d * texHeight) / spriteHeight) / 256;
                    Uint32 color = pTexture[texX + (texY * texHeight)];
                    //paint pixel if it isn't black, black is the invisible color
                    if ((color & 0x00FFFFFF) != 0) {
                        m_pGameSurface->putPixel(stripe, y, color);
                    }
                }
            }
        }
    }
}

void RayCast::combSort(int* pOrder, double* pDist, int amount) {
    int gap = amount;
    bool swapped = false;
    while(gap > 1 || swapped) {
        //shrink factor 1.3
        gap = (gap * 10) / 13;
        if(gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < amount - gap; i++) {
            int j = i + gap;
            if (pDist[i] < pDist[j]) {
                std::swap(pDist[i], pDist[j]);
                std::swap(pOrder[i], pOrder[j]);
                swapped = true;
            }
        }
    }
}
