#include "MainMenuState.hpp"
#include "../TextureManager.hpp"
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
    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++) {
        TheTextureManager::Instance()->
            clearFromTextureMap(m_textureIDList[i]);
    }

    std::cout << "exiting MainMenuState\n";
    return true;
}


void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    // empty
}


