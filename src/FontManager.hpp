#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>

using std::string;
using std::map;

struct FontStruct {
    SDL_Texture* texture;
    int width;
    int height;

    FontStruct(SDL_Texture* tex, int w, int h)
        : texture(tex), width(w), height(h) {}
    ~FontStruct() {
        SDL_DestroyTexture(texture);
    }
};

class FontParams {
    public:
        FontParams(string id, int x, int y, int scale = 1, int spacing = 1) 
        : m_id(id), m_x(x), m_y(y), m_scale(scale), m_spacing(spacing) {};
        string getId() const { return m_id; }
        int getX() const { return m_x; }
        int getY() const { return m_y; }
        int getScale() const { return m_scale; }
        int getSpacing() const { return m_spacing; }

    private:
        string m_id;
        int m_x;
        int m_y;
        int m_scale;
        int m_spacing;
};

class FontManager {
    public:
        static FontManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new FontManager();
            }
            return s_pInstance;
        }

        bool load(string fileName, string id, int letterWidth, int letterHeight,
                SDL_Renderer* pRenderer);
        void draw(const string text, const FontParams &params,
                SDL_Renderer* pRenderer);
        void clearFromFontMap(string id);

    private:
        FontManager();
        ~FontManager();

        static FontManager* s_pInstance;
        static const std::string s_letters;

        map<string, FontStruct*> m_fontMap;

        SDL_Rect sourceRectangle(int character, const FontParams &params);
        SDL_Rect destinationRectangle(int charIndex, const FontParams &params);

};

typedef FontManager TheFontManager;

#endif

