#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>

using std::string;
using std::map;

class TextureManager {
    public:
        static TextureManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new TextureManager();
            }
            return s_pInstance;
        }

        bool load(string fileName, string id, SDL_Renderer* pRenderer);
        void draw(string id, SDL_Rect rect, SDL_Renderer* pRenderer,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
        void clearFromTextureMap(string id);

    private:
        TextureManager();

        static TextureManager* s_pInstance;

        map<string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif

