#include "BitmapManager.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

BitmapManager* BitmapManager::s_pInstance = 0;

BitmapManager::BitmapManager() {
    setPixelFormat("resources/surfaceFormat.png");
}

bool BitmapManager::load(string fileName, string id) {
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    if (pSurface == 0) {
        return false;
    }

    vector<Uint32> pixels = getPixelsFromSurface(pSurface);

    SDL_FreeSurface(pSurface);

    int bitmapSize = 64*64;
    pixels.resize(bitmapSize);


    Uint32* pFinalPixels = new Uint32[bitmapSize];
    for (int i = 0; i < bitmapSize; i++) {
        pFinalPixels[i] = pixels[i];
    }

    m_bitmapMap[id] = pFinalPixels;
    return true;
}

Uint32* BitmapManager::getBitmap(string id) {
    return m_bitmapMap[id];
}

void BitmapManager::setPixelFormat(string fileName) {
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    if (pSurface == 0) {
        std::cerr << "Format image has not been found.\n";
        return;
    }

    m_pixelFormat = *pSurface->format;

}

void BitmapManager::clearFromBitmapMap(string id) {
    delete m_bitmapMap[id];
    m_bitmapMap.erase(id);
}

vector<Uint32> BitmapManager::getPixelsFromSurface(SDL_Surface *pSurface) {
    int bpp = pSurface->format->BytesPerPixel;
    int width = pSurface->w;
    int height = pSurface->h;
    vector<Uint32> pixels;


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint8* p = (Uint8 *)pSurface->pixels + y * pSurface->pitch + x * bpp;
            Uint32 pixel = convertPixel(p, bpp);
            pixels.push_back(pixel);
        }
    }

    return pixels;
}

Uint32 BitmapManager::convertPixel(Uint8* p, int bpp) {
    Uint32 pixel = 0;
    switch (bpp) {
        case 1:
            pixel = *p;
            break;
        case 2:
            pixel = *(Uint16 *)p;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                pixel = p[0] << 16 | p[1] << 8 | p[2];
            } else {
                pixel = p[0] | p[1] << 8 | p[2] << 16;
            }
            break;
        case 4:
            pixel = *(Uint32 *)p;
            break;
        default:
            pixel = 0;
            break;
    }
    return pixel;
}
