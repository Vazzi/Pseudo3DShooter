#include "Map.hpp"
#include <iostream>

Map::Map(const int height, const int width) {
    m_height = height;
    m_width = width;
    m_map = new int[width * height];
}

Map::~Map() {
    m_walls.clear();
}

void Map::loadMap(int array[]) {
    for (unsigned int i = 0; i < (m_height * m_width); i++) {
        m_map[i] = array[i];
    }
}

string Map::getWallTextureID(const unsigned int x, const unsigned int y) const {
    if (x < m_width && y < m_height) {
        int wallIndex = m_map[x + (m_width * y)];
        if (wallIndex > 0 && (unsigned int)wallIndex <= m_walls.size()) {
            wallIndex--; // 0 is no object but objects index starts from 0
            return m_walls[wallIndex];
        }
    }
    return "";
}

bool Map::isEmpty(const unsigned int x, const unsigned int y) {
    if (x < m_width && y < m_height) {
        if (m_map[x + (m_width * y)] == 0) {
            return true;
        }
    }
    return false;
}

bool Map::isWall(const unsigned int x, const unsigned int y) {
    if (x < m_width && y < m_height) {
        return m_map[x + (m_width * y)];
    }
    return false;
}
