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

    std::string pointer = ">";

    int xOffset = TheFontManager::Instance()->getLetterWidth(m_fontID, m_scale)
        * pointer.size();
    Vector2D offset = Vector2D(xOffset, 0);

    if (active) {
        m_position -= offset;
        m_text = pointer + m_text;
    } else {
        m_text = m_text.substr(pointer.size(), m_text.length() - 1);
        m_position += offset;
    }
}


