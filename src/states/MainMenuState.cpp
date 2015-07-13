#include "MainMenuState.hpp"
#include "../TextureManager.hpp"
#include "../FontManager.hpp"
#include <iostream>

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() {
    // empty
}

void MainMenuState::render() {
    // empty
}

bool MainMenuState::onEnter() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    std::cout << "entering MainMenuState\n";
    return true;
}

bool MainMenuState::onExit() {

    std::cout << "exiting MainMenuState\n";
    return true;
}


void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    // empty
}


