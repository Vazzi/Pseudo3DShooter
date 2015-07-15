#ifndef __MENU_BUTTON__
#define __MENU_BUTTON__

#include "TextObject.hpp"

class MenuButton : public TextObject {
    public:
        MenuButton();

        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);

        void setCallback(void(*callback)()) { m_callback = callback;}
        int getCallbackID() { return m_callbackID; }
        void setActive(bool active);

    private:
        void (*m_callback) ();

        int m_callbackID;
        bool m_isActive;
};

#endif

