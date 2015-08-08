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
    if (x < m_width && y < m_height) {
        m_pBuffer[x + (y * m_width)] = pixel;
    }
}

void GameSurface::draw(int x, int y, int width, int height) {
    bufferToSurface();
    drawSurface(x, y, width, height);
}

void GameSurface::drawSurface(int x, int y, int width, int height) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(
            TheGame::Instance()->getRenderer(), m_pSurface);

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

    SDL_RenderCopy(TheGame::Instance()->getRenderer(),
            pTexture, &srcRect, &destRect);
}

void GameSurface::clear() {
    SDL_FillRect(m_pSurface, NULL, 0);
}

void GameSurface::bufferToSurface() {
    Uint32* pPixel;
    pPixel = (Uint32*)m_pSurface->pixels;
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            *pPixel = m_pBuffer[x + (y * m_width)];
            pPixel++;
        }
    }
}

