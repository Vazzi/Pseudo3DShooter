#include "SurfaceManager.hpp"

#include <SDL2/SDL_image.h>

SurfaceManager* SurfaceManager::s_pInstance = 0;

bool SurfaceManager::load(string fileName, string id) {
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    if (pSurface == 0) {
        return false;
    }

    m_surfaceMap[id] = pSurface;
    return true;
}

SDL_Surface* SurfaceManager::getSurface(string id) {
    if (m_surfaceMap.find(id) != m_surfaceMap.end()) {
        return m_surfaceMap[id];
    }
    return NULL;
}

void SurfaceManager::clearFromSurfaceMap(string id) {
    if (m_surfaceMap.find(id) != m_surfaceMap.end()) {
        SDL_FreeSurface(m_surfaceMap[id]);
        m_surfaceMap.erase(id);
    }
}

