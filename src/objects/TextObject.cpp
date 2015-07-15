#include "TextObject.hpp"

#include "../Game.hpp"

TextObject::TextObject() : GameObject(), m_position(Vector2D(0, 0)),
    m_color(FontColor(255, 255, 255)) {
    // empty
}

void TextObject::render() {
    FontParams params = FontParams(m_fontID, m_position, m_color,
            m_scale, m_spacing);
    TheFontManager::Instance()->draw(m_text, params,
            TheGame::Instance()->getRenderer());
}

void TextObject::update() {
    // empty
}

void TextObject::clean() {
    // empty
}

void TextObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_fontID = pParams->getTextureID();
    m_spacing = 1;
    m_scale = 1;
}

void TextObject::setColor(int r, int g, int b) {
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
}
