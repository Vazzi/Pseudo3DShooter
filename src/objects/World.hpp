#ifndef __WORLD__
#define __WORLD__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include "../utility/RayCast.hpp"
#include <vector>

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
        RayCast* m_pRayCast;
        Map* m_pMap;
        Player* m_pPlayer;
        std::vector<GameObject*> m_gameObjects;
        std::vector<std::string> m_textureIDs;

};

class WorldCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new World();
    }
};


#endif
