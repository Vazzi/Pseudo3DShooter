#include "WorldObject.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Game.hpp"
#include "../InputHandler.hpp"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

WorldObject::WorldObject() {
    m_keyTime = 0;
    m_posX = 22;
    m_posY = 12;
    m_dirX = -1;
    m_dirY = 0;
    m_planeX = 0;
    m_planeY = 0.66;
    m_time = 0;
    m_oldTime = 0;
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

        //choose wall color
        SDL_Color color;
        color.r = 0;
        color. b = 0;
        color.g = 0;
        switch(worldMap[mapX][mapY]) {
            case 1:  color.r = 255;  break; //red
            case 2:  color.g = 255;  break; //green
            case 3:  color.b = 255;   break; //blue
            case 4:  color.r = 255; color.b = 255; color.g = 255;  break; //white
            default: color.r = 255; color.g = 255; break; //yellow
        }
        //give x and y sides different brightness
        //if (side == 1) {color = color / 2;}

        //draw the pixels of the stripe as a vertical line
        //verLine(x, drawStart, drawEnd, color);

        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), color.r, color.g, color.b, 255);
        SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), x, drawStart, x, drawEnd);
        SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
    }
}

void WorldObject::update(unsigned int deltaTime) {
    if (m_keyTime > 0) {
        m_keyTime -= deltaTime;
        return;
    } else {
        m_keyTime = 50;
    }

    //speed modifiers
    double moveSpeed = 0.5; //the constant value is in squares/second
    double rotSpeed = 0.3; //the constant value is in radians/second

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

