#ifndef __BITMAP_MANAGER__
#define __BITMAP_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>

using std::map;
using std::string;

class BitmapManager {
    public:
        static BitmapManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new BitmapManager();
            }
            return s_pInstance;
        }

        bool load(string fileName, string id);
        SDL_Surface* getSurface(string id);
        SDL_Surface* getFirstSurface();
        void clearFromSurfaceMap(string id);

    private:
        BitmapManager();

        static BitmapManager* s_pInstance;

        map<string, SDL_Surface*> m_surfaceMap;
};

typedef BitmapManager TheBitmapManager;

#endif
