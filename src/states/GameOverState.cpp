#include "GameOverState.hpp"
#include "../json/StateParser.hpp"
#include "../Game.hpp"
#include "GameStateMachine.hpp"


const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update(unsigned int deltaTime) {
    MenuState::update(deltaTime);
}

void GameOverState::render() {
    GameState::render();
}

bool GameOverState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_gameOverID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    if (!MenuState::onEnter()) {
        return false;
    }

    initCallbacks();

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }

    std::cout << "exiting GameOverState\n";
    return true;
}

void GameOverState::s_exitFromGameOver() {
    TheGame::Instance()->getStateMachine()->popState();
}

void GameOverState::initCallbacks() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_exitFromGameOver);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
}

