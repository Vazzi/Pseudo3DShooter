#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "MenuState.hpp"

class PauseState : public MenuState {
    public:
        virtual void update(unsigned int deltaTime);
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_pauseID; }

    private:
        static const std::string s_pauseID;

        static void s_resumePlay();
        static void s_pauseToMain();

        void initCallbacks();

};
#endif

