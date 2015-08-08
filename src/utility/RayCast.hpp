#ifndef __RAY_CAST__
#define __RAY_CAST__

#include <vector>
#include "../utility/Ray.hpp"
#include <SDL2/SDL.h>

class Map;
class Player;
class GameObject;
class GameSurface;

using std::vector;

class RayCast {
    public:
        RayCast(Map* pMap, Player* pPlayer, vector<GameObject*>* pGameObjects);
        ~RayCast();
        void setSurface(int width, int height, int scale);
        void drawWorld();
        void render(int x, int y, int width, int height);

    private:
        vector<GameObject*>* m_pGameObjects;
        Map* m_pMap;
        Player* m_pPlayer;
        SDL_Surface* m_pFloorTexture;
        SDL_Surface* m_pCeilingTexture;
        GameSurface* m_pGameSurface;
        int m_drawEnd;

        void drawWalls(int x, Ray &ray);
        void drawFloorAndCeiling(int x, Ray &ray);
        void drawSprites(int x, Ray &ray);
};

#endif