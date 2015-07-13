#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <string>
#include <vector>

class GameState {
    public:
        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool onEnter() = 0;
        virtual bool onExit() = 0;

        virtual std::string getStateID() const = 0;

        virtual ~GameState() {}

   protected:
       std::vector<std::string> m_textureIDList;

};

#endif

