#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string>
#include <vector>

class GameObject;

class GameState {
    public:
        virtual void update(unsigned int deltaTime);
        virtual void render();

        virtual bool onEnter() = 0;
        virtual bool onExit();

        virtual std::string getStateID() const = 0;

        virtual ~GameState() {}

    protected:
        std::vector<std::string> m_textureIDList;
        std::vector<GameObject*> m_gameObjects;

};

#endif

