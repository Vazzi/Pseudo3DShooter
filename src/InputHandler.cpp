#include "InputHandler.hpp"
#include "Game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() {
    // empty
}
void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                TheGame::Instance()->quit();
                break;
            default:
                break;
        }
    }
}

void InputHandler::clean() {
    // empty
}
