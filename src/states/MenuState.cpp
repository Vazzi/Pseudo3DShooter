#include "MenuState.hpp"
#include "../InputHandler.hpp"
#include "../objects/MenuButton.hpp"

const int KEY_WAIT_TIME = 150;

MenuState::MenuState() : m_activeButton(0), m_keyTime(0) {
    // empty
}

bool MenuState::onEnter() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        // if they are of type MenuButton then assign t
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            m_menuButtons.push_back(pButton);
        }
    }
    return true;
}

void MenuState::update(unsigned int deltaTime) {
    GameState::update(deltaTime);

    if (m_keyTime <= 0) {
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
            if (m_activeButton != 0) {
                m_activeButton = (m_activeButton - 1);
            }
            m_keyTime = KEY_WAIT_TIME;
        } else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
            if (m_activeButton != m_menuButtons.size() - 1) {
                m_activeButton = (m_activeButton + 1);
            }
            m_keyTime = KEY_WAIT_TIME;
        }
        updateButtons();
    } else {
        m_keyTime -= deltaTime;
    }
}

void MenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    for (int i = 0; i < m_menuButtons.size(); i++) {
        // if they are of type MenuButton then assign a callback
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_menuButtons[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_menuButtons[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MenuState::updateButtons() {
    for (int i = 0; i < m_menuButtons.size(); i++) {
        MenuButton* pButton = dynamic_cast<MenuButton*>(m_menuButtons[i]);
        if (i == m_activeButton) {
            pButton->setActive(true);
        } else {
            pButton->setActive(false);
        }
    }
}
