#include "InputHandler.hpp"
#include "Game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_keystates(0) {
    // empty
}

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                TheGame::Instance()->quit();
                break;
            case SDL_KEYDOWN:
                onKeyDown();
                break;
            case SDL_KEYUP:
                onKeyUp();
                break;
            default:
                break;
        }
    }
}

void InputHandler::clean() {
    // empty
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void InputHandler::onKeyDown(){
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
    m_keystates = SDL_GetKeyboardState(0);
}

