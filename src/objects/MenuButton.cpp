#include "MenuButton.hpp"

#include "../InputHandler.hpp"
#include <SDL2/SDL.h>

#include <iostream>

MenuButton::MenuButton() : TextObject(), m_callbackID(0) {
    // empty
}

void MenuButton::render() {
    TextObject::render();
}

void MenuButton::update() {
    TextObject::update();
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)
            && m_isActive) {
        m_callback();
    }
}

void MenuButton::clean() {
    TextObject::clean();
}

void MenuButton::load(const LoaderParams* pParams) {
    TextObject::load(pParams);
    m_isActive = false;
    m_callbackID = pParams->getCallbackID();
}

void MenuButton::setActive(bool active) {
    if (active == m_isActive) {
        return;
    }

    m_isActive = active;

    if (active) {
        m_text = ">" + m_text;
    } else {
        m_text = m_text.substr(1, m_text.length() - 1);
    }
}


