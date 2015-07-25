#include "MainMenuState.hpp"
#include "../objects/MenuButton.hpp"
#include "../Game.hpp"
#include <iostream>
#include "StateParser.hpp"
#include "AboutState.hpp"
#include "GameStateMachine.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update(unsigned int deltaTime) {
    MenuState::update(deltaTime);
}

void MainMenuState::render() {
    GameState::render();
}

bool MainMenuState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_menuID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    if (!MenuState::onEnter()) {
        return false;
    }

    initCallbacks();

    std::cout << "entering MainMenuState\n";
    return true;
}

bool MainMenuState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }

    std::cout << "exiting MainMenuState\n";
    return true;
}

void MainMenuState::s_menuToPlay() {
    // empty
}

void MainMenuState::s_menuToAbout() {
    TheGame::Instance()->getStateMachine()->pushState(new AboutState());
}

void MainMenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
}

void MainMenuState::initCallbacks() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_menuToAbout);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
}

