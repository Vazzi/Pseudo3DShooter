#ifndef __BITMAP_MANAGER__
#define __BITMAP_MANAGER__

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class BitmapManager {
    public:
        static BitmapManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new BitmapManager();
            }
            return s_pInstance;
        }

        bool load(string fileName, string id);
        Uint32* getBitmap(string id);
        void setPixelFormat(string fileName);
        SDL_PixelFormat* getPixelFormat() { return &m_pixelFormat; }
        void clearFromBitmapMap(string id);

    private:
        BitmapManager();

        static BitmapManager* s_pInstance;

        map<string, Uint32*> m_bitmapMap;
        SDL_PixelFormat m_pixelFormat;

        vector<Uint32> getPixelsFromSurface(SDL_Surface *pSurface);
        Uint32 convertPixel(Uint8* p, int bpp);
};

typedef BitmapManager TheBitmapManager;

#endif
