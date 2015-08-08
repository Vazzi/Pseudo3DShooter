#ifndef __WORLD__
#define __WORLD__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
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

        Map* m_pMap;
        Player* m_pPlayer;
        std::vector<GameObject*> m_gameObjects;
        GameSurface* m_pGameSurface;
        double m_time;
        double m_oldTime;

        void renderSurface();
        void drawWalls();

};

class WorldCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new World();
    }
};


#endif
