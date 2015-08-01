#include "Map.hpp"
#include <iostream>

Map::Map(const int height, const int width) {
    m_height = height;
    m_width = width;
    m_map = new int[width * height];
}

Map::~Map() {
    for (unsigned int i = 0; i < m_walls.size(); i++) {
        SDL_FreeSurface(m_walls[i]);
    }
    m_walls.clear();
}

void Map::loadMap(int array[]) {
    for (unsigned int i = 0; i < (m_height * m_width); i++) {
        m_map[i] = array[i];
    }
}

bool Map::loadWallBitmap(std::string fileName) {
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == 0) {
        std::cerr << "File " << fileName << " was not found.\n";
        return false;
    }
    m_walls.push_back(pTempSurface);
    return true;
}

SDL_Surface* Map::getWall(const unsigned int x, const unsigned int y) {
    if (x < m_width && y < m_height) {
        int wallIndex = m_map[x + (m_width * y)];
        if (wallIndex > 0 && (unsigned int)wallIndex <= m_walls.size()) {
            wallIndex--; // 0 is no object but objects index starts from 0
            return m_walls[wallIndex];
        }
    }
    return NULL;
}

bool Map::isEmpty(const unsigned int x, const unsigned int y) {
    if (x < m_width && y < m_height) {
        return !(m_map[x + (m_width * y)]);
    }
    return true;
}

// TODO: What is wall and what is object?
bool Map::isWall(const unsigned int x, const unsigned int y) {
    if (x < m_width && y < m_height) {
        return m_map[x + (m_width * y)];
    }
    return false;
}
