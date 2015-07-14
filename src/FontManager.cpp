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

    for (int i = 0; i < text.length(); i++){
        char c = text[i];
        int chr = s_letters.find_first_of(c, 0);
        if (chr < 0) {
            continue;
        }

        int xOffset = chr % 42;
        int yOffset = chr / 42;

        FontStruct* font = m_fontMap[params.getId()];
        int spacing = 1;

        SDL_Rect srcRect;
        SDL_Rect destRect;

        srcRect.x = xOffset * (font->width + spacing);
        srcRect.y = yOffset * font->height;
        srcRect.w = font->width;
        srcRect.h = font->height;
        destRect.w = font->width * params.getScale();
        destRect.h = font->height * params.getScale();
        destRect.x = params.getX() + i * (font->width + params.getSpacing())
            * params.getScale();
        destRect.y = params.getX();

        SDL_RenderCopy(pRenderer, font->texture, &srcRect,  &destRect);

    }
}

void FontManager::clearFromFontMap(string id) {
    delete m_fontMap[id];
    m_fontMap.erase(id);
}


