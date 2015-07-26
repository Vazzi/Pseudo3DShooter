#include "PlayState.hpp"
#include "StateParser.hpp"
#include "../InputHandler.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(unsigned int deltaTime) {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        //TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    GameState::update(deltaTime);
}

void PlayState::render() {
    GameState::render();
}

bool PlayState::onEnter() {
    StateParser stateParser;
    stateParser.parseState("resources/data.json", s_playID, &m_gameObjects,
            &m_textureIDList, &m_fontIDList);

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit() {
    if (!GameState::onExit()) {
        return false;
    }
    std::cout << "exiting PlayState\n";
    return true;
}

