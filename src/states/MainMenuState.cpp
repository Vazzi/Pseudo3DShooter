#include "MainMenuState.hpp"
#include "../TextureManager.hpp"
#include "../FontManager.hpp"
#include <iostream>
#include "../objects/GameObject.hpp"
#include "../objects/MenuButton.hpp"

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

    MenuButton* pButton = new MenuButton();
    LoaderParams *params = new LoaderParams(100, 100, 500, 0, "basicFont");
    pButton->load(params);
    pButton->setText("Play");
    pButton->setScale(5);
    m_gameObjects.push_back(pButton);

    MenuButton* pButton2 = new MenuButton();
    LoaderParams *params2 = new LoaderParams(100, 200, 500, 0, "basicFont");
    pButton2->load(params2);
    pButton2->setText("Quit");
    pButton2->setScale(5);
    m_gameObjects.push_back(pButton2);

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


