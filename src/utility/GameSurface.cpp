#include "GameSurface.hpp"
#include "../Game.hpp"
#include <algorithm>

GameSurface::GameSurface(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
    int colorDepth = 32;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    m_pSurface = SDL_CreateRGBSurface(0, width, height, colorDepth, rmask, gmask, bmask, amask);

    m_pBuffer = new Uint32[width * height];
}

void GameSurface::setFormatBySurface(SDL_Surface* pSurface) {
    m_pSurface->format = pSurface->format;
}

GameSurface::~GameSurface() {
    SDL_FreeSurface(m_pSurface);
    delete m_pBuffer;
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
    std::fill(m_pBuffer, m_pBuffer + (m_width * m_height), 0);
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

