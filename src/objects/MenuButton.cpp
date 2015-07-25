#include "MenuButton.hpp"
#include "../InputHandler.hpp"

MenuButton::MenuButton() : TextObject(), m_callbackID(0) {
    // empty
}

void MenuButton::render() {
    TextObject::render();
}

void MenuButton::update(unsigned int deltaTime) {
    TextObject::update(deltaTime);
}

void MenuButton::click() {
    m_callback();
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


