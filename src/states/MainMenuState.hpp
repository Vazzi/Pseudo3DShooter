#ifndef __MAIN_MENU_STATE__
#define __MAIN_MENU_STATE__

#include "MenuState.hpp"

class GameObject;

class MainMenuState : public MenuState {
    public:
        virtual void update(unsigned int deltaTime);
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_menuID; }
    private:
        static const std::string s_menuID;

        static void s_menuToPlay();
        static void s_exitFromMenu();

        void initCallbacks();
        void initObjects();

};
#endif

