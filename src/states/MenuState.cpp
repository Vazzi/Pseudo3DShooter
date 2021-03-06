#include "MenuState.hpp"
#include "../InputHandler.hpp"
#include "../objects/MenuButton.hpp"
#include "../managers/SoundManager.hpp"

const int KEY_WAIT_TIME = 150;

MenuState::MenuState() : m_activeButton(0), m_keyTime(KEY_WAIT_TIME) {
    // empty
}

bool MenuState::onEnter() {
    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        // if they are of type MenuButton then assign t
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            m_menuButtons.push_back(pButton);
        }
    }
    updateButtons();
    return true;
}

void MenuState::update(unsigned int deltaTime) {
    GameState::update(deltaTime);

    if (m_keyTime <= 0) {
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
            if (m_activeButton != 0) {
                m_activeButton = (m_activeButton - 1);
            }
            resetKeyTime();
            updateButtons();
        } else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
            if (m_activeButton != (int)m_menuButtons.size() - 1) {
                m_activeButton = (m_activeButton + 1);
            }
            resetKeyTime();
            updateButtons();
        } else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
            TheSoundManager::Instance()->playSound("click", 0);
            resetKeyTime();
            m_menuButtons[m_activeButton]->click();
        }
    } else {
        m_keyTime -= deltaTime;
    }
}

void MenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    for (unsigned long i = 0; i < m_menuButtons.size(); i++) {
        // if they are of type MenuButton then assign a callback
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_menuButtons[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_menuButtons[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MenuState::updateButtons() {
    for (unsigned long i = 0; i < m_menuButtons.size(); i++) {
        MenuButton* pButton = dynamic_cast<MenuButton*>(m_menuButtons[i]);
        if (i == (unsigned long)m_activeButton) {
            pButton->setActive(true);
        } else {
            pButton->setActive(false);
        }
    }
}

void MenuState::resetKeyTime() {
    m_keyTime = KEY_WAIT_TIME;
}
