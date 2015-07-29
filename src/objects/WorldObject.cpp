#include "WorldObject.hpp"
#include "../Game.hpp"
#include "../InputHandler.hpp"
#include <fstream>

SDL_Surface* scr;
Uint32 buffer[640][480];
int worldMap[24][24]=
{
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
    {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
    {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
    {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
    {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
    {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
    {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

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

WorldObject::WorldObject() {
    m_posX = 22;
    m_posY = 11.5;
    m_dirX = -1;
    m_dirY = 0;
    m_planeX = 0;
    m_planeY = 0.66;
    m_time = 0;
    m_oldTime = 0;

    texture.push_back(IMG_Load("resources/eagle.png"));
    texture.push_back(IMG_Load("resources/redbrick.png"));
    texture.push_back(IMG_Load("resources/purplestone.png"));
    texture.push_back(IMG_Load("resources/greystone.png"));
    texture.push_back(IMG_Load("resources/bluestone.png"));
    texture.push_back(IMG_Load("resources/mossy.png"));
    texture.push_back(IMG_Load("resources/wood.png"));
    texture.push_back(IMG_Load("resources/colorstone.png"));

    int w = TheGame::Instance()->getWidth();
    int h = TheGame::Instance()->getHeight();
    int colorDepth = 32;
    SDL_Surface *surface;

    scr = SDL_CreateRGBSurface(0, w, h, colorDepth, 0, 0, 0, 0);
}

void WorldObject::render() {
    double w = TheGame::Instance()->getWidth();
    double h = TheGame::Instance()->getHeight();

    for(int x = 0; x < w; x++) {
        //calculate ray position and direction
        double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
        double rayPosX = m_posX;
        double rayPosY = m_posY;
        double rayDirX = m_dirX + m_planeX * cameraX;
        double rayDirY = m_dirY + m_planeY * cameraX;
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
            if (worldMap[mapX][mapY] > 0) {
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
        int lineHeight = abs(int(h / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawEnd >= h)drawEnd = h - 1;

        //texturing calculations
        int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 1) {
            wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
        } else {
            wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
        }
        wallX -= floor((wallX));

        int texWidth = 64;
        int texHeight = 64;

        //x coordinate on the texture
        int texX = int(wallX * double(texWidth));
        if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        for(int y = drawStart; y<drawEnd; y++) {
            int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            int texY = ((d * texHeight) / lineHeight) / 256;
            Uint32 color = getpixel(texture[texNum], texX, texY);
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
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

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            putpixel(scr, x, y, buffer[x][y]);
        }
    }

    if ( SDL_MUSTLOCK(scr) ) {
        SDL_UnlockSurface(scr);
    }
    redraw();
    for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) buffer[x][y] = 0;

}

void WorldObject::update(unsigned int deltaTime) {
    //speed modifiers
    double moveSpeed = 5.0 * (deltaTime / 1000.0); //the constant value is in squares/second
    double rotSpeed = 3.0 * (deltaTime / 1000.0); //the constant value is in radians/second

    //move forward if no wall in front of you
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        if(worldMap[int(m_posX + m_dirX * moveSpeed)][int(m_posY)] == false) m_posX += m_dirX * moveSpeed;
        if(worldMap[int(m_posX)][int(m_posY + m_dirY * moveSpeed)] == false) m_posY += m_dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        if(worldMap[int(m_posX - m_dirX * moveSpeed)][int(m_posY)] == false) m_posX -= m_dirX * moveSpeed;
        if(worldMap[int(m_posX)][int(m_posY - m_dirY * moveSpeed)] == false) m_posY -= m_dirY * moveSpeed;
    }
    //rotate to the right
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        //both camera m_direction and camera m_plane must be rotated
        double oldm_dirX = m_dirX;
        m_dirX = m_dirX * cos(-rotSpeed) - m_dirY * sin(-rotSpeed);
        m_dirY = oldm_dirX * sin(-rotSpeed) + m_dirY * cos(-rotSpeed);
        double oldm_planeX = m_planeX;
        m_planeX = m_planeX * cos(-rotSpeed) - m_planeY * sin(-rotSpeed);
        m_planeY = oldm_planeX * sin(-rotSpeed) + m_planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        //both camera m_direction and camera m_plane must be rotated
        double oldm_dirX = m_dirX;
        m_dirX = m_dirX * cos(rotSpeed) - m_dirY * sin(rotSpeed);
        m_dirY = oldm_dirX * sin(rotSpeed) + m_dirY * cos(rotSpeed);
        double oldm_planeX = m_planeX;
        m_planeX = m_planeX * cos(rotSpeed) - m_planeY * sin(rotSpeed);
        m_planeY = oldm_planeX * sin(rotSpeed) + m_planeY * cos(rotSpeed);
    }
}

void WorldObject::clean() {
    // empty
}

void WorldObject::load(const LoaderParams* pParams) {

}

