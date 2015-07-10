#include "Game.hpp"
#include <iostream>

Game* Game::s_pInstance = 0;

Game::Game() : m_isRunning(false) {
    // empty
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width,
        bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        std::cout << "SDL init success\n";
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }

    return true;
}

void Game::render(Uint32 deltaTime) {
    // emtpy
}

void Game::update(Uint32 deltaTime) {
    // emtpy
}

void Game::handleEvents(Uint32 deltaTime) {
    // emtpy
}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_Quit();
}

void Game::quit() {
    m_isRunning = false;
}

bool Game::running() {
    return m_isRunning;
}

