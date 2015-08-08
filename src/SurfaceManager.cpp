#include "SurfaceManager.hpp"

#include <SDL2/SDL_image.h>

SurfaceManager* SurfaceManager::s_pInstance = 0;

SurfaceManager::SurfaceManager() {
    // empty
}

bool SurfaceManager::load(string fileName, string id) {
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    if (pSurface == 0) {
        return false;
    }

    m_surfaceMap[id] = pSurface;
    return true;
}

SDL_Surface* SurfaceManager::getSurface(string id) {
    return m_surfaceMap[id];
}

void SurfaceManager::clearFromSurfaceMap(string id) {
    SDL_FreeSurface(m_surfaceMap[id]);
    m_surfaceMap.erase(id);
}

