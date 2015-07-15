#include "TextObject.hpp"

#include "../Game.hpp"


TextObject::TextObject() : GameObject(), m_position(Vector2D(0, 0)),
    m_color(FontColor(255, 255, 255)), m_flashColor(FontColor(255, 255, 255)),
    m_flashTime(0), m_flashRate(0), m_currentColorIndex(0) {
    // empty
}

void TextObject::render() {
    if (m_currentColorIndex == 0) {
        renderFontWithColor(m_color);
    } else {
        renderFontWithColor(m_flashColor);
    }
}

void TextObject::renderFontWithColor(FontColor color) {
    FontParams params = FontParams(m_fontID, m_position, color,
            m_scale, m_spacing);
    TheFontManager::Instance()->draw(m_text, params,
            TheGame::Instance()->getRenderer());
}

void TextObject::update(unsigned int deltaTime) {
    // Flash only if flashRate is setup
    if (m_flashRate != 0) {
        if (m_flashTime <= 0) {
            m_currentColorIndex = (m_currentColorIndex + 1) % 2;
            m_flashTime = m_flashRate;
        } else {
            m_flashTime -= deltaTime;
        }
    }
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
    m_flashColor.r = r;
    m_flashColor.g = g;
    m_flashColor.b = b;
}

void TextObject::setColorFlash(int r, int g, int b, unsigned int flashRate) {
    m_flashColor.r = r;
    m_flashColor.g = g;
    m_flashColor.b = b;
    m_flashRate = flashRate;
}
