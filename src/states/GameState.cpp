#include "GameState.hpp"

#include "../objects/GameObject.hpp"

void GameState::render() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->render();
    }
}

void GameState::update() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

bool GameState::onExit() {
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    return true;
}
