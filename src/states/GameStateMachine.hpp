#ifndef __GAME_STATE_MACHINE__
#define __GAME_STATE_MACHINE__

#include <vector>

class GameState;

class GameStateMachine {
    public:
        ~GameStateMachine();
        void update();
        void render();
        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();
    private:
        std::vector<GameState*> m_gameStates;
};

#endif

