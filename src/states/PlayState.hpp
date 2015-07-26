#ifndef __PLAY_STATE__
#define __PLAY_STATE__

#include "GameState.hpp"

class PlayState : public GameState {
    public:
        virtual void update(unsigned int deltaTime);
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_playID; }

    private:
        static const std::string s_playID;
};

#endif

