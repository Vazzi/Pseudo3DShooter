#include "Game.hpp"

#include <iostream>
#include "InputHandler.hpp"

Game* Game::s_pInstance = 0;

Game::Game() : m_isRunning(false) {
    m_pWindow = 0;
    m_pRenderer = 0;
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        std::cout << "SDL init success\n";
        if (!initWindow("Game", 100, 100, 640, 480, false)) {
            return false;
        }
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
    TheInputHandler::Instance()->update();
}

void Game::handleEvents(Uint32 deltaTime) {
    // emtpy
}

void Game::clean() {
    std::cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::quit() {
    m_isRunning = false;
}

bool Game::running() {
    return m_isRunning;
}

bool Game::initWindow(const char* title, int xpos, int ypos, int height, int width,
        bool fullscreen) {

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
    if (m_pWindow != 0) {
        std::cout << "window creation success\n";
        if (!initRenderer()) {
            return false;
        }
    } else {
        std::cout << "window init fail\n";
        return false;
    }

    m_isRunning = true;
    return true;
}

bool Game::initRenderer() {
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
            SDL_RENDERER_ACCELERATED);
    if (m_pRenderer != 0) {
        std::cout << "renderer creation success\n";
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    } else {
        std::cout << "renderer init fail\n";
        return false;
    }
    return true;
}

