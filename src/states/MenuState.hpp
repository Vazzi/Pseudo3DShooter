#ifndef __MENU_STATE__
#define __MENU_STATE__

#include "GameState.hpp"
#include <vector>

class MenuButton;

class MenuState : public GameState {
    public:
        MenuState();

        virtual void update(unsigned int deltaTime);
        virtual bool onEnter();
    protected:
        typedef void(*Callback)();

        std::vector<Callback> m_callbacks;
        std::vector<MenuButton*> m_menuButtons;
        int m_activeButton;
        int m_keyTime;

        virtual void setCallbacks(const std::vector<Callback>& callbacks);

        void updateButtons();
        void resetKeyTime();

};
#endif

