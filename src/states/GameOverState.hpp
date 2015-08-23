#ifndef __GAME_OVER_STATE__
#define __GAME_OVER_STATE__

#include "MenuState.hpp"

class GameOverState : public MenuState{
    public:

        virtual void update(unsigned int deltaTime);
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_gameOverID; }
    private:
        static const std::string s_gameOverID;

        static void s_exitFromGameOver();

        void initCallbacks();
};
#endif
