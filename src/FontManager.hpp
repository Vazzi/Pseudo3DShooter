#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <SDL2/SDL.h>
#include <string>

using std::string;

class FontManager {
    public:
        static FontManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new FontManager();
            }
            return s_pInstance;
        }

        bool load(SDL_Renderer* pRenderer);
        void draw(string text, SDL_Rect rect, SDL_Renderer* pRenderer);

    private:
        FontManager();
        ~FontManager();

        static FontManager* s_pInstance;
        static const std::string s_letters;

        SDL_Texture* m_pFontTexture;

};

typedef FontManager TheFontManager;

#endif

