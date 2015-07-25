#include "GameState.hpp"

#include "../objects/GameObject.hpp"
#include "../FontManager.hpp"
#include "../TextureManager.hpp"

void GameState::render() {
    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->render();
    }
}

void GameState::update(unsigned int deltaTime) {
    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update(deltaTime);
    }
}

bool GameState::onExit() {
    for (unsigned long i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    // clear the texture manager
    for(unsigned long i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // clear the font manager
    for(unsigned long i = 0; i < m_fontIDList.size(); i++) {
        TheFontManager::Instance()->clearFromFontMap(m_fontIDList[i]);
    }

    return true;
}
