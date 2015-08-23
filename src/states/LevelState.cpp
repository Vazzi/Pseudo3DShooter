#include "LevelState.hpp"
#include "../json/StateParser.hpp"
#include "../InputHandler.hpp"
#include "GameStateMachine.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "../Game.hpp"
#include "../objects/World.hpp"
#include "../objects/Player.hpp"
#include "../managers/SoundManager.hpp"

const std::string LevelState::s_playID = "LEVEL";

void LevelState::update(unsigned int deltaTime) {
    GameState::update(deltaTime);
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    } else if (ThePlayer::Instance()->getHealth() <= 0) {
        TheSoundManager::Instance()->playSound("gasp", 0);
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }
}

void LevelState::render() {
    GameState::render();
}

bool LevelState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_playID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

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

