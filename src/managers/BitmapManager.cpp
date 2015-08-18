#include "BitmapManager.hpp"

#include <SDL2/SDL_image.h>

BitmapManager* BitmapManager::s_pInstance = 0;

BitmapManager::BitmapManager() {
    // empty
}

bool BitmapManager::load(string fileName, string id) {
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    if (pSurface == 0) {
        return false;
    }

    m_surfaceMap[id] = pSurface;
    return true;
}

SDL_Surface* BitmapManager::getSurface(string id) {
    return m_surfaceMap[id];
}

SDL_Surface* BitmapManager::getFirstSurface() {
    if (m_surfaceMap.empty()) {
        return NULL;
    }
    return m_surfaceMap.begin()->second;
}

void BitmapManager::clearFromSurfaceMap(string id) {
    SDL_FreeSurface(m_surfaceMap[id]);
    m_surfaceMap.erase(id);
}

