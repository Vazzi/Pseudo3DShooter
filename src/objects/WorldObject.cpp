#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../InputHandler.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Vector2D.hpp"
#include "../states/StateParser.hpp"
#include <fstream>

SDL_Surface* scr;
Uint32 buffer[640][480];

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;

   default:
        break;           /* shouldn't happen, but avoids warnings */
    } // switch
}

Uint32 getpixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    } // switch
}

void redraw() {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scr);

    SDL_Rect srcRect;
    SDL_Rect destRect;

    destRect.x = srcRect.x = 0;
    destRect.y = srcRect.y = 0;
    srcRect.w = destRect.w = 640;
    srcRect.h = destRect.h = 480;

    SDL_RenderCopy(TheGame::Instance()->getRenderer(), pTexture, &srcRect, &destRect);
}

WorldObject::WorldObject() : m_position(Vector2D(0, 0)) {
    // empty
}

void WorldObject::render() {
    for(int x = 0; x < m_width; x++) {
        //calculate ray position and direction
        double cameraX = 2 * x / m_width - 1; //x-coordinate in camera space
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
            if (m_pMap->isEmpty(mapX, mapY)) {
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
        int texX = int(wallX * double(pTexture->w));
        if (side == 0 && rayDirX > 0) texX = pTexture->w - texX - 1;
        if (side == 1 && rayDirY < 0) texX = pTexture->w - texX - 1;
        for (int y = drawStart; y<drawEnd; y++) {
            int d = y * 256 - m_height * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            int texY = ((d * pTexture->h) / lineHeight) / 256;
            Uint32 color = getpixel(pTexture, texX, texY);
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            // TODO: Darker color
            //if(side == 1) color = (color >> 1) & 8355711;
            buffer[x][y] = color;
        }

    }

    if ( SDL_MUSTLOCK(scr) ) {
        if ( SDL_LockSurface(scr) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            putpixel(scr, x, y, buffer[x][y]);
        }
    }

    if ( SDL_MUSTLOCK(scr) ) {
        SDL_UnlockSurface(scr);
    }
    redraw();
    for(int x = 0; x < m_width; x++) for(int y = 0; y < m_height; y++) buffer[x][y] = 0;

}

void WorldObject::update(unsigned int deltaTime) {
    //speed modifiers
    //double moveSpeed = 5.0 * (deltaTime / 1000.0); //the constant value is in squares/second
    //double rotSpeed = 3.0 * (deltaTime / 1000.0); //the constant value is in radians/second

    //int posX = m_pPlayer->getPosition().getX();
    //int posY = m_pPlayer->getPosition().getY();


    ////move forward if no wall in front of you
    //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        //// TODO: m_pPlayer->nextStepX();
        //if (!m_pMap->isEmpty(posX + m_pPlayer->getDirX() * moveSpeed, posY)) {
            //// TODO: m_pPlayer->moveX();
            //m_pPlayer->alterPosition(m_pPlayer->getDirX() * moveSpeed, 0);
        //}
        //// TODO: m_pPlayer->nextStepY();
        //if(!m_pMap->isEmpty(posX, posY + m_pPlayer->getDirY() * moveSpeed)) {
            //// TODO: m_pPlayer->moveY();
            //m_pPlayer->alterPosition(0, m_pPlayer->getDirY() * moveSpeed);
        //}
    //}
    // TODO: implement the rest
    ////move backwards if no wall behind you
    //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
    //if(worldMap[int(m_posX - m_dirX * moveSpeed)][int(m_posY)] == false) m_posX -= m_dirX * moveSpeed;
    //if(worldMap[int(m_posX)][int(m_posY - m_dirY * moveSpeed)] == false) m_posY -= m_dirY * moveSpeed;
    //}
    ////rotate to the right
    //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
    ////both camera m_direction and camera m_plane must be rotated
    //double oldm_dirX = m_dirX;
    //m_dirX = m_dirX * cos(-rotSpeed) - m_dirY * sin(-rotSpeed);
    //m_dirY = oldm_dirX * sin(-rotSpeed) + m_dirY * cos(-rotSpeed);
    //double oldm_planeX = m_planeX;
    //m_planeX = m_planeX * cos(-rotSpeed) - m_planeY * sin(-rotSpeed);
    //m_planeY = oldm_planeX * sin(-rotSpeed) + m_planeY * cos(-rotSpeed);
    //}
    ////rotate to the left
    //if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
    ////both camera m_direction and camera m_plane must be rotated
    //double oldm_dirX = m_dirX;
    //m_dirX = m_dirX * cos(rotSpeed) - m_dirY * sin(rotSpeed);
    //m_dirY = oldm_dirX * sin(rotSpeed) + m_dirY * cos(rotSpeed);
    //double oldm_planeX = m_planeX;
    //m_planeX = m_planeX * cos(rotSpeed) - m_planeY * sin(rotSpeed);
    //m_planeY = oldm_planeX * sin(rotSpeed) + m_planeY * cos(rotSpeed);
    //}

}

void WorldObject::clean() {
    // empty
}

void WorldObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_height = pParams->getHeight();
    m_width = pParams->getWidth();
    m_planeX = 0;
    m_planeY = 0.66;
    m_time = 0;
    m_oldTime = 0;

    int colorDepth = 32;
    SDL_Surface *surface;
    scr = SDL_CreateRGBSurface(0, m_width, m_height, colorDepth, 0, 0, 0, 0);
}

void WorldObject::loadLevelData(std::string fileName) {
    StateParser parser;
    parser.parseWorld(fileName.c_str(), &m_gameObjects, m_pMap, m_pPlayer);
}


