#include "GameSurface.hpp"
#include "../Game.hpp"

GameSurface::GameSurface(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
    int colorDepth = 32;
    m_pSurface = SDL_CreateRGBSurface(0, width, height, colorDepth, 0, 0, 0, 0);

    m_pBuffer = new Uint32[width * height];
}

void GameSurface::setFormatBySurface(SDL_Surface* pSurface) {
    m_pSurface->format = pSurface->format;
}


GameSurface::~GameSurface() {
    SDL_FreeSurface(m_pSurface);
    delete m_pBuffer;
}

Uint32 GameSurface::getPixelFromSurface(SDL_Surface *pSurface, int x, int y) {
    int bpp = pSurface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)pSurface->pixels + y * pSurface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                return p[0] << 16 | p[1] << 8 | p[2];
            } else {
                return p[0] | p[1] << 8 | p[2] << 16;
            }
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void GameSurface::putPixel(int x, int y, Uint32 pixel) {
    lock();
    if (x < m_width && y < m_height) {
        m_pBuffer[x + (y * m_width)] = pixel;
    }
    unlock();
}

void GameSurface::draw(int x, int y, int width, int height) {
    bufferToSurface();
    drawSurface(x, y, width, height);
}

void GameSurface::drawSurface(int x, int y, int width, int height) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), m_pSurface);

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_width;
    srcRect.h = m_height;
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopy(TheGame::Instance()->getRenderer(), pTexture, &srcRect, &destRect);
}

void GameSurface::clear() {
    unsigned int size = m_width * m_height;
    for (unsigned int i = 0; i < size; i++) {
        m_pBuffer[i] = 0;
    }
}

void GameSurface::bufferToSurface() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            putPixelToSurface(x, y, m_pBuffer[x + (m_width *y)]);
        }
    }
}

void GameSurface::lock() {
    if (SDL_MUSTLOCK(m_pSurface)) {
        if (SDL_LockSurface(m_pSurface) < 0) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
        }
    }
}

void GameSurface::unlock() {
    if (SDL_MUSTLOCK(m_pSurface)) {
        SDL_UnlockSurface(m_pSurface);
    }
}

void GameSurface::putPixelToSurface(int x, int y, Uint32 pixel) {
    int bpp = m_pSurface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set 
    Uint8 *p = (Uint8 *)m_pSurface->pixels + y * m_pSurface->pitch + x * bpp;

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
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
        default:
            break;
    }
}

