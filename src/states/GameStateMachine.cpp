#include "GameStateMachine.hpp"
#include "GameState.hpp"

GameStateMachine::~GameStateMachine() {
    for (std::vector<GameState *>::iterator it = m_gameStates.begin();
            it != m_gameStates.end(); ++it) {
        delete *it;
    }
    m_gameStates.clear();
}

void GameStateMachine::update(unsigned int deltaTime) {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update(deltaTime);
    }
}

void GameStateMachine::render() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(GameState* pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(GameState *pState) {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }
        if (m_gameStates.back()->onExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }

    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

