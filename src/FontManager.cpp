#include "FontManager.hpp"

#include <SDL2/SDL_image.h>

FontManager* FontManager::s_pInstance = 0;

const string FontManager::s_letters = ""
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?\"'/\\<>()[]{}"
            "abcdefghijklmnopqrstuvwxyz_               "
            "0123456789+-=*:;ÖÅÄå                      "
            "";

const int FONT_WIDTH = 5;
const int FONT_HEIGHT = 8;


FontManager::FontManager() : m_pFontTexture(0) {
    // empty
}

FontManager::~FontManager() {
    // empty
}


bool FontManager::load(SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load("resources/font.png");

    if (pTempSurface == 0) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0) {
        m_pFontTexture = pTexture;
        return true;
    }

    return false;
}

void FontManager::draw(string text, SDL_Rect rect, SDL_Renderer* pRenderer) {

    for (int i = 0; i < text.length(); i++){
        char c = text[i];
        int chr = s_letters.find_first_of(c, 0);
        if (chr < 0) {
            continue;
        }

        int xOffset = chr % 42;
        int yOffset = chr / 42;

        SDL_Rect srcRect;
        SDL_Rect destRect;

        // TODO: Scale as global or something
        int scale = 6;

        srcRect.x = xOffset * (FONT_WIDTH + 1);
        srcRect.y = yOffset * FONT_HEIGHT;
        srcRect.w = FONT_WIDTH;
        srcRect.h = FONT_HEIGHT;
        destRect.w = FONT_WIDTH * scale;
        destRect.h = FONT_HEIGHT * scale;
        destRect.x = rect.x + i * (FONT_WIDTH + 1) * scale;
        destRect.y = rect.y;

        SDL_RenderCopy(pRenderer, m_pFontTexture, &srcRect,  &destRect);

    }

}


