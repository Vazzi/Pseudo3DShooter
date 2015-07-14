#include "MainMenuState.hpp"
#include "../TextureManager.hpp"
#include "../FontManager.hpp"
#include <iostream>
#include "../objects/GameObject.hpp"
#include "../objects/TextObject.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() {
    GameState::update();
}

void MainMenuState::render() {
    GameState::render();
}

bool MainMenuState::onEnter() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    TextObject* pText = new TextObject();
    LoaderParams *params = new LoaderParams(100, 100, 500, 0, "basicFont");
    pText->load(params);
    pText->setText("This is my game");
    pText->setScale(5);
    m_gameObjects.push_back(pText);

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


void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
    // empty
}


