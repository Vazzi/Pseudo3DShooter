#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "utility/Vector2D.hpp"

using std::string;
using std::map;

struct FontStruct {
    SDL_Texture* texture;
    int width;
    int height;
    int refCounter;

    FontStruct(SDL_Texture* tex, int w, int h)
        : texture(tex), width(w), height(h), refCounter(1) {}
    ~FontStruct() {
        SDL_DestroyTexture(texture);
    }
};

struct FontColor {
    int r;
    int g;
    int b;

    FontColor(int r, int g, int b) : r(r), g(g), b(b) {}
};

class FontParams {
    public:
        FontParams(string id, Vector2D position, FontColor color, int scale = 1,
                int spacing = 1) : m_id(id), m_pos(position), m_color(color),
        m_scale(scale), m_spacing(spacing) {};

        string getId() const { return m_id; }
        float getX() const { return m_pos.getX(); }
        float getY() const { return m_pos.getY(); }
        Vector2D getPosition() const { return m_pos; }
        FontColor getColor() const { return m_color; }
        int getScale() const { return m_scale; }
        int getSpacing() const { return m_spacing; }

    private:
        string m_id;
        Vector2D m_pos;
        FontColor m_color;
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
        int getLetterWidth(std::string fontID, int scale = 1);

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

