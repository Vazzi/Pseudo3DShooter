#ifndef __SURFACE_MANAGER__
#define __SURFACE_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>

using std::map;
using std::string;

class SurfaceManager {
    public:
        static SurfaceManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new SurfaceManager();
            }
            return s_pInstance;
        }

        bool load(string fileName, string id);
        SDL_Surface* getSurface(string id);
        SDL_Surface* getFirstSurface();
        void clearFromSurfaceMap(string id);

    private:
        SurfaceManager();

        static SurfaceManager* s_pInstance;

        map<string, SDL_Surface*> m_surfaceMap;
};

typedef SurfaceManager TheSurfaceManager;

#endif
