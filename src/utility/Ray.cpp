#include "Ray.hpp"
#include "../objects/Player.hpp"
#include "../objects/Map.hpp"

Ray::Ray(int x, double width, Player* pPlayer) {
    double cameraX = 2 * x / double(width) - 1;

    m_posX = pPlayer->getPosition().getX();
    m_posY = pPlayer->getPosition().getY();
    m_dirX = pPlayer->getDirX() + pPlayer->getPlaneX() * cameraX;
    m_dirY = pPlayer->getDirY() + pPlayer->getPlaneY() * cameraX;
    // Ray on map
    m_mapX = int(m_posX);
    m_mapY = int(m_posY);
    // Length of ray from one x or y-side to next x or y-side
    m_deltaDistX = sqrt(1 + (m_dirY * m_dirY) / (m_dirX * m_dirX));
    m_deltaDistY = sqrt(1 + (m_dirX * m_dirX) / (m_dirY * m_dirY));

    m_wallDist = -1;

}

void Ray::performDDA(Map* pMap) {
    setStepAndSideDist();

    int hit = 0; // was there a wall hit?

    // Perform DDA
    while (hit == 0) {
        // Jump to next map square, OR in x-direction, OR in y-direction
        if (m_sideDistX < m_sideDistY) {
            m_sideDistX += m_deltaDistX;
            makeStepX();
            m_side = 0;
        } else {
            m_sideDistY += m_deltaDistY;
            makeStepY();
            m_side = 1;
        }
        //Check if ray has hit a wall
        if (pMap->isWall(m_mapX, m_mapY)) {
            hit = 1;
        }
    }
}

double Ray::getWallDist() const {
    // If wall is already computed
    if (m_wallDist != -1) {
        return m_wallDist;
    }
    // Calculate distance projected on camera direction
    // (oblique distance will give fisheye effect!)
    if (m_side == 0) {
        return fabs((m_mapX - m_posX + (1 - m_stepX) / 2) / m_dirX);
    } else {
        return fabs((m_mapY - m_posY + (1 - m_stepY) / 2) / m_dirY);
    }
}

double Ray::getWallX() const {
    //where exactly the wall was hit
    double wallX;
    if (m_side == 1) {
        wallX = m_posX + ((m_mapY - m_posY + (1 - m_stepY) / 2) / m_dirY) * m_dirX;
    } else {
        wallX = m_posY + ((m_mapX - m_posX + (1 - m_stepX) / 2) / m_dirX) * m_dirY;
    }
    wallX -= floor(wallX);
    return wallX;
}

void Ray::setStepAndSideDist() {
    // Calculate step and initial sideDist
    if (m_dirX < 0) {
        m_stepX = -1;
        m_sideDistX = (m_posX - m_mapX) * m_deltaDistX;
    } else {
        m_stepX = 1;
        m_sideDistX = (m_mapX + 1.0 - m_posX) * m_deltaDistX;
    }
    if (m_dirY < 0) {
        m_stepY = -1;
        m_sideDistY = (m_posY - m_mapY) * m_deltaDistY;
    } else {
        m_stepY = 1;
        m_sideDistY = (m_mapY + 1.0 - m_posY) * m_deltaDistY;
    }
}


