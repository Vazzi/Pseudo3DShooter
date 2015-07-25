#ifndef __ABOUT_STATE__
#define __ABOUT_STATE__

#include "MenuState.hpp"

class GameObject;

class AboutState : public MenuState {
    public:
        virtual void update(unsigned int deltaTime);
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_aboutID; }
    private:
        static const std::string s_aboutID;

        static void s_exitFromAbout();

        void initCallbacks();
};
#endif

