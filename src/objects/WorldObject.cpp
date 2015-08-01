#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../InputHandler.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "../states/StateParser.hpp"
#include <fstream>
#include "../utility/GameSurface.hpp"

WorldObject::WorldObject() : m_position(Vector2D(0, 0)) {
    // empty
}

void WorldObject::render() {
    drawWalls();
    renderSurface();
}

void WorldObject::update(unsigned int deltaTime) {
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

void WorldObject::clean() {
    delete m_pGameSurface;
    m_pPlayer->clean();
    delete m_pPlayer;
    delete m_pMap;

    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

}

void WorldObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_height = pParams->getHeight();
    m_width = pParams->getWidth();
    m_time = 0;
    m_oldTime = 0;
    float scale = 1;
    m_pGameSurface = new GameSurface(m_width * scale, m_height * scale);
}

void WorldObject::loadLevelData(std::string fileName) {
    StateParser parser;
    parser.parseWorld(fileName.c_str(), &m_gameObjects, &m_pMap, &m_pPlayer);
}

void WorldObject::renderSurface() {
    m_pGameSurface->draw(m_position.getX(), m_position.getY(), m_width, m_height);
    m_pGameSurface->clear();
}

void WorldObject::drawWalls() {
    for (int x = 0; x < m_pGameSurface->getWidth(); x++) {
        double cameraX = 2 * x / double(m_pGameSurface->getWidth()) - 1;
        // calculate ray position and direction
        double rayPosX = m_pPlayer->getPosition().getX();
        double rayPosY = m_pPlayer->getPosition().getY();
        double rayDirX = m_pPlayer->getDirX() + m_pPlayer->getPlaneX() * cameraX;
        double rayDirY = m_pPlayer->getDirY() + m_pPlayer->getPlaneY() * cameraX;
        // Where is player
        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // was there a wall hit?
        int side; // was a NS or a EW wall hit?
        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (rayPosX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (rayPosY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0) {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (m_pMap->isWall(mapX, mapY)) {
                hit = 1;
            }
        }

        // Calculate distance projected on camera direction 
        // (oblique distance will give fisheye effect!)
        if (side == 0) {
            perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        } else {
            perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
        }

        // Calculate height of line to draw on screen
        int lineHeight = abs(int(m_pGameSurface->getHeight() / perpWallDist));

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + m_pGameSurface->getHeight() / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + m_pGameSurface->getHeight() / 2;
        if (drawEnd >= m_pGameSurface->getHeight()) {
            drawEnd = m_pGameSurface->getHeight() - 1;
        }

        // Calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 1) {
            wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
        } else {
            wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
        }
        wallX -= floor((wallX));

        // Get texture calculations
        SDL_Surface* pTexture = m_pMap->getWall(mapX, mapY);

        //x coordinate on the texture
        int texX = int(wallX * double(pTexture->w));
        if (side == 0 && rayDirX > 0) {
            texX = pTexture->w - texX - 1;
        }
        if (side == 1 && rayDirY < 0) {
            texX = pTexture->w - texX - 1;
        }
        for (int y = drawStart; y<drawEnd; y++) {
            //256 and 128 factors to avoid floats
            int d = y * 256 - m_pGameSurface->getHeight() * 128 + lineHeight * 128;
            int texY = ((d * pTexture->h) / lineHeight) / 256;
            Uint32 color = GameSurface::getPixelFromSurface(pTexture, texX, texY);
            m_pGameSurface->putPixel(x, y, color);
        }

        // FLOOR CASTING
        double floorXWall, floorYWall;

        // 4 different wall directions possible
        if(side == 0 && rayDirX > 0) {
            floorXWall = mapX;
            floorYWall = mapY + wallX;
        } else if(side == 0 && rayDirX < 0) {
            floorXWall = mapX + 1.0;
            floorYWall = mapY + wallX;
        } else if(side == 1 && rayDirY > 0) {
            floorXWall = mapX + wallX;
            floorYWall = mapY;
        } else {
            floorXWall = mapX + wallX;
            floorYWall = mapY + 1.0;
        }

        double distWall, distPlayer, currentDist;

        distWall = perpWallDist;
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
            floorTexX = int(currentFloorX * pTexture->w) % pTexture->w;
            floorTexY = int(currentFloorY * pTexture->h) % pTexture->h;

            pTexture = m_pMap->getFloor();
            Uint32 color = GameSurface::getPixelFromSurface(pTexture, floorTexX, floorTexY);
            color = (color >> 1) & 8355711;
            m_pGameSurface->putPixel(x, y, color);

            pTexture = m_pMap->getCeiling();
            color = GameSurface::getPixelFromSurface(pTexture, floorTexX, floorTexY);
            color = (color >> 1) & 8355711;
            m_pGameSurface->putPixel(x, m_height-y, color);
        }
    }

}

