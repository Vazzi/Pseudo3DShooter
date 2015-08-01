#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Map {
    public:
        Map(const int width , const int height);
        ~Map ();
        void loadMap(int array[]);
        bool loadWallBitmap(const std::string fileName);
        bool loadObjectBitmap(const std::string fileName);
        bool loadFloorBitmap(const std::string fileName);
        bool loadCeilingBitmap(const std::string fileName);
        SDL_Surface* getWall(const unsigned int x, const unsigned int y);
        SDL_Surface* getObject(const unsigned int x, const unsigned int y);
        SDL_Surface* getFloor() { return m_pFloor; };
        SDL_Surface* getCeiling() { return m_pCeiling; };
        bool isEmpty(const unsigned int x, const unsigned int y);
        bool isWall(const unsigned int x, const unsigned int y);

    private:
        int* m_map;
        std::vector<SDL_Surface*> m_walls;
        std::vector<SDL_Surface*> m_objects;
        SDL_Surface* m_pFloor;
        SDL_Surface* m_pCeiling;
        unsigned int m_width;
        unsigned int m_height;
};

#endif
