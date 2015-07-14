#include "FontManager.hpp"

#include <SDL2/SDL_image.h>

FontManager* FontManager::s_pInstance = 0;

const string FontManager::s_letters = ""
"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?\"'/\\<>()[]{}"
"abcdefghijklmnopqrstuvwxyz_               "
"0123456789+-=*:;ÖÅÄå                      "
"";

FontManager::FontManager() {
    // empty
}

FontManager::~FontManager() {
    // empty
}

bool FontManager::load(string fileName, string id, int width, int height,
        SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == 0) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0) {
        m_fontMap[id] = new FontStruct(pTexture, width, height);
        return true;
    }

    return false;
}

void FontManager::draw(string text, const FontParams &params,
        SDL_Renderer* pRenderer) {

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        int chr = s_letters.find_first_of(c, 0);
        if (chr < 0) {
            continue;
        }

        SDL_Rect srcRect = sourceRectangle(chr, params);
        SDL_Rect destRect = destinationRectangle(i, params);
        SDL_Texture* pTexture = m_fontMap[params.getId()]->texture;

        SDL_RenderCopy(pRenderer, pTexture, &srcRect,  &destRect);
    }
}

void FontManager::clearFromFontMap(string id) {
    delete m_fontMap[id];
    m_fontMap.erase(id);
}

SDL_Rect FontManager::sourceRectangle(int character, const FontParams &params) {
    int xOffset = character % 42;
    int yOffset = character / 42;
    FontStruct* font = m_fontMap[params.getId()];

    SDL_Rect srcRect;

    srcRect.x = xOffset * (font->width + params.getSpacing());
    srcRect.y = yOffset * font->height;
    srcRect.w = font->width;
    srcRect.h = font->height;

    return srcRect;
}

SDL_Rect FontManager::destinationRectangle(int charIndex, const FontParams &params) {
    FontStruct* font = m_fontMap[params.getId()];
    SDL_Rect destRect;

    destRect.w = font->width * params.getScale();
    destRect.h = font->height * params.getScale();
    destRect.x = params.getX() + charIndex * (font->width + params.getSpacing())
        * params.getScale();
    destRect.y = params.getX();

    return destRect;
}


