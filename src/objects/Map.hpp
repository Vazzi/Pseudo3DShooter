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
        // TODO: Rename wall to objects
        bool loadWallBitmap(const std::string fileName);
        SDL_Surface* getWall(const unsigned int x, const unsigned int y);
        bool isEmpty(const unsigned int x, const unsigned int y);
        bool isWall(const unsigned int x, const unsigned int y);

    private:
        int* m_map;
        std::vector<SDL_Surface*> m_walls;
        unsigned int m_width;
        unsigned int m_height;
};

#endif
