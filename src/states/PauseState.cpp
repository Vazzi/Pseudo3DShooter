#include "PauseState.hpp"
#include "../json/StateParser.hpp"
#include "MainMenuState.hpp"
#include "GameStateMachine.hpp"
#include "../Game.hpp"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update(unsigned int deltaTime) {
    MenuState::update(deltaTime);
}

void PauseState::render() {
    GameState::render();
}

bool PauseState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_pauseID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    if (!MenuState::onEnter()) {
        return false;
    }

    initCallbacks();

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::s_resumePlay() {
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::s_pauseToMain() {
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::initCallbacks() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_resumePlay);
    m_callbacks.push_back(s_pauseToMain);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
}

