#include "MainMenuState.hpp"
#include "../objects/MenuButton.hpp"
#include "../Game.hpp"
#include <iostream>
#include "StateParser.hpp"

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
            &m_textureIDList);

    initObjects();
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

void MainMenuState::s_exitFromMenu() {
    TheGame::Instance()->quit();
}

void MainMenuState::initCallbacks() {
    m_callbacks.push_back(0); // pushback 0 callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
}

// TODO: Remove this method after JSON parser
void MainMenuState::initObjects() {
    TextObject* pText = new TextObject();
    LoaderParams *pTextParams= new LoaderParams(60, 50, 500, 0, "basicFont");
    pText->load(pTextParams);
    pText->setScale(5);
    pText->setColor(255, 0, 0);
    pText->setColorFlash(150, 0, 0, 500);
    pText->setText("PSEUDO 3D SHOOTER");
    m_gameObjects.push_back(pText);

    MenuButton* pButton = new MenuButton();
    LoaderParams *pParams = new LoaderParams(100, 150, 500, 0, "basicFont", 1);
    pButton->load(pParams);
    pButton->setText("Play");
    pButton->setScale(4);
    m_gameObjects.push_back(pButton);
    m_menuButtons.push_back(pButton);

    MenuButton* pButton2 = new MenuButton();
    LoaderParams *pParams2 = new LoaderParams(100, 200, 500, 0, "basicFont", 2);
    pButton2->load(pParams2);
    pButton2->setText("Something cool");
    pButton2->setScale(4);
    m_gameObjects.push_back(pButton2);
    m_menuButtons.push_back(pButton2);

    MenuButton* pButton3 = new MenuButton();
    LoaderParams *pParams3 = new LoaderParams(100, 250, 500, 0, "basicFont", 2);
    pButton3->load(pParams3);
    pButton3->setText("Quit");
    pButton3->setScale(4);
    m_gameObjects.push_back(pButton3);
    m_menuButtons.push_back(pButton3);
}

