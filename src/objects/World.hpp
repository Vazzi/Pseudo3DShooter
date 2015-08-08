#ifndef __WORLD__
#define __WORLD__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include "../utility/Ray.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map;
class Player;
class GameSurface;

class World : public GameObject {
    public:
        World();

        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);
        void loadLevelData(std::string fileName);

    private:
        Vector2D m_position;
        int m_height;
        int m_width;
        int m_drawEnd;

        Map* m_pMap;
        Player* m_pPlayer;
        std::vector<GameObject*> m_gameObjects;
        std::vector<std::string> m_textureIDs;
        GameSurface* m_pGameSurface;
        double m_time;
        double m_oldTime;

        void renderSurface();
        void drawWorld();
        void drawWalls(int x, Ray &ray);
        void drawFloorAndCeiling(int x, Ray &ray, SDL_Surface* pFloor,
                SDL_Surface *pCeiling);
        void drawSprites(int x, Ray &ray);

};

class WorldCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new World();
    }
};


#endif
