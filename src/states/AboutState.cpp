#include "AboutState.hpp"
#include "StateParser.hpp"
#include "GameStateMachine.hpp"
#include "../Game.hpp"

const std::string AboutState::s_aboutID = "ABOUT";

void AboutState::update(unsigned int deltaTime) {
    MenuState::update(deltaTime);
}

void AboutState::render() {
    GameState::render();
}

bool AboutState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_aboutID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    if (!MenuState::onEnter()) {
        return false;
    }

    initCallbacks();

    std::cout << "entering AboutState\n";
    return true;
}

bool AboutState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }

    std::cout << "exiting AboutState\n";
    return true;
}

void AboutState::s_exitFromAbout() {
    TheGame::Instance()->getStateMachine()->popState();
}

void AboutState::initCallbacks() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_exitFromAbout);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
}

