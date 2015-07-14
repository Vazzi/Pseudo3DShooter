#include "MainMenuState.hpp"
#include "../TextureManager.hpp"
#include "../FontManager.hpp"
#include <iostream>
#include "../objects/GameObject.hpp"
#include "../objects/MenuButton.hpp"
#include "../Game.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() {
    GameState::update();
}

void MainMenuState::render() {
    GameState::render();
}

bool MainMenuState::onEnter() {
    MenuButton* pButton = new MenuButton();
    LoaderParams *params = new LoaderParams(100, 100, 500, 0, "basicFont", 1);
    pButton->load(params);
    pButton->setText("Play");
    pButton->setScale(5);
    m_gameObjects.push_back(pButton);

    MenuButton* pButton2 = new MenuButton();
    LoaderParams *params2 = new LoaderParams(100, 200, 500, 0, "basicFont", 2);
    pButton2->load(params2);
    pButton2->setText("Quit");
    pButton2->setScale(5);
    pButton2->setActive(true);
    m_gameObjects.push_back(pButton2);

    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);

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
    for (int i = 0; i < m_gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MainMenuState::s_menuToPlay() {
    // empty
}

void MainMenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
}


