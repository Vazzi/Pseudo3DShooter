#ifndef __WORLD_OBJECT__
#define __WORLD_OBJECT__

#include "GameObject.hpp"
#include "Vector2D.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map;
class Player;

class WorldObject : public GameObject {
    public:
        WorldObject();

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
        double m_planeX;
        double m_planeY;
        double m_time;
        double m_oldTime;

};

class WorldObjectCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new WorldObject();
    }
};


#endif
