#include "LevelState.hpp"
#include "StateParser.hpp"
#include "../InputHandler.hpp"
#include "GameStateMachine.hpp"
#include "PauseState.hpp"
#include "../Game.hpp"
#include "../objects/WorldObject.hpp"

const std::string LevelState::s_playID = "LEVEL";

void LevelState::update(unsigned int deltaTime) {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    GameState::update(deltaTime);
}

void LevelState::render() {
    GameState::render();
}

bool LevelState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_playID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    m_gameObjects.push_back(new WorldObject());

    std::cout << "entering LevelState\n";
    return true;
}

bool LevelState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }
    std::cout << "exiting LevelState\n";
    return true;
}

