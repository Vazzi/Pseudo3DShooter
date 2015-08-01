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

// TODO: texture size
    int textureWidth = 64;
    int textureHeight = 64;
    for(int x = 0; x < m_width; x++) {
        //calculate ray position and direction
        double cameraX = 2 * x / double(m_width) - 1; //x-coordinate in camera space
        double rayPosX = m_pPlayer->getPosition().getX();
        double rayPosY = m_pPlayer->getPosition().getY();
        double rayDirX = m_pPlayer->getDirX() + m_planeX * cameraX;
        double rayDirY = m_pPlayer->getDirY() + m_planeY * cameraX;
        //which box of the map we're in
        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
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
        //perform DDA
        while (hit == 0) {
            //jump to next map square, OR in x-direction, OR in y-direction
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
        //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
        if (side == 0) {
            perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        } else {
            perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
        }

        //Calculate height of line to draw on screen
        int lineHeight = abs(int(m_height / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + m_height / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + m_height / 2;
        if(drawEnd >= m_height)drawEnd = m_height - 1;

        //texturing calculations
        SDL_Surface* pTexture = m_pMap->getWall(mapX, mapY);

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 1) {
            wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
        } else {
            wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
        }
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = int(wallX * double(textureWidth));
        if (side == 0 && rayDirX > 0) texX = textureWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = textureWidth - texX - 1;
        for (int y = drawStart; y<drawEnd; y++) {
            int d = y * 256 - m_height * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            int texY = ((d * textureHeight) / lineHeight) / 256;
            Uint32 color = GameSurface::getPixelFromSurface(pTexture, texX, texY);
            m_pGameSurface->putPixel(x, y, color);
        }
    }

    m_pGameSurface->draw(m_position.getX(), m_position.getY(), m_width, m_height);
    m_pGameSurface->clear();
}

void WorldObject::update(unsigned int deltaTime) {
    //speed modifiers
    double moveSpeed = 5.0 * (deltaTime / 1000.0); //the constant value is in squares/second
    double rotSpeed = 3.0 * (deltaTime / 1000.0); //the constant value is in radians/second

    double posX = m_pPlayer->getPosition().getX();
    double posY = m_pPlayer->getPosition().getY();

    //move forward if no wall in front of you
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        // TODO: m_pPlayer->nextStepX();
        if (m_pMap->isEmpty(posX + m_pPlayer->getDirX() * moveSpeed, posY)) {
            // TODO: m_pPlayer->moveX();
            m_pPlayer->alterPosition(m_pPlayer->getDirX() * moveSpeed, 0);
        }
        // TODO: m_pPlayer->nextStepY();
        if(m_pMap->isEmpty(posX, posY + m_pPlayer->getDirY() * moveSpeed)) {
            // TODO: m_pPlayer->moveY();
            m_pPlayer->alterPosition(0, m_pPlayer->getDirY() * moveSpeed);
        }
    }
    // TODO: implement the rest
    //move backwards if no wall behind you
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        if (m_pMap->isEmpty(int(posX - m_pPlayer->getDirX() * moveSpeed), posY)) {
            m_pPlayer->alterPosition((m_pPlayer->getDirX() * moveSpeed * -1), 0);
        }
        if (m_pMap->isEmpty(int(posX), int(posY - m_pPlayer->getDirY() * moveSpeed))) {
            m_pPlayer->alterPosition(0, -1 * m_pPlayer->getDirY() * moveSpeed);
        }
    }
    //rotate to the right
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        //both camera m_direction and camera m_plane must be rotated
        double oldm_dirX = m_pPlayer->getDirX();
        m_pPlayer->setDirX(m_pPlayer->getDirX() * cos(-rotSpeed) - m_pPlayer->getDirY() * sin(-rotSpeed));
        m_pPlayer->setDirY(oldm_dirX * sin(-rotSpeed) + m_pPlayer->getDirY() * cos(-rotSpeed));
        double oldm_planeX = m_planeX;
        m_planeX = m_planeX * cos(-rotSpeed) - m_planeY * sin(-rotSpeed);
        m_planeY = oldm_planeX * sin(-rotSpeed) + m_planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        //both camera m_direction and camera m_plane must be rotated
        double oldm_dirX = m_pPlayer->getDirX();
        m_pPlayer->setDirX(m_pPlayer->getDirX() * cos(rotSpeed) - m_pPlayer->getDirY() * sin(rotSpeed));
        m_pPlayer->setDirY(oldm_dirX * sin(rotSpeed) + m_pPlayer->getDirY() * cos(rotSpeed));
        double oldm_planeX = m_planeX;
        m_planeX = m_planeX * cos(rotSpeed) - m_planeY * sin(rotSpeed);
        m_planeY = oldm_planeX * sin(rotSpeed) + m_planeY * cos(rotSpeed);
    }

}

void WorldObject::clean() {
    delete m_pGameSurface;
    delete m_pPlayer;
    delete m_pMap;
    // TODO: Delete everything
}

void WorldObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_height = pParams->getHeight();
    m_width = pParams->getWidth();
    m_planeX = 0;
    m_planeY = 0.66;
    m_time = 0;
    m_oldTime = 0;
    m_pGameSurface = new GameSurface(m_width, m_height);
}

void WorldObject::loadLevelData(std::string fileName) {
    StateParser parser;
    parser.parseWorld(fileName.c_str(), &m_gameObjects, &m_pMap, &m_pPlayer);
}


