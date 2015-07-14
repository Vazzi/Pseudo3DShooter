#include "TextureManager.hpp"

#include <SDL2/SDL_image.h>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager() {
    // empty
}

bool TextureManager::load(string fileName, string id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == 0) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0) {
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;

}

void TextureManager::draw(string id, SDL_Rect rect,  SDL_Renderer* pRenderer,
        SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = rect.w;
    srcRect.h = destRect.h = rect.h;
    destRect.x = rect.x;
    destRect.y = rect.y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,  &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(string id) {
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}
