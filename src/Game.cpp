#include "Game.hpp"

#include <iostream>
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "states/GameStateMachine.hpp"
#include "states/MainMenuState.hpp"
#include "objects/GameObjectFactory.hpp"
#include "objects/TextObject.hpp"
#include "objects/MenuButton.hpp"

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

    initGameObjects();
    initStateMachine();

    if (!TheFontManager::Instance()->load("resources/font.png",
                "basicFont", 5, 8, m_pRenderer)) {
        return false;
    }

    m_isRunning = true;

    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    m_pStateMachine->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::update(unsigned int deltaTime) {
    m_pStateMachine->update(deltaTime);
}

void Game::handleEvents() {
    TheInputHandler::Instance()->update();
}

void Game::clean() {
    std::cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();
    delete m_pStateMachine;

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

GameStateMachine* Game::getStateMachine() {
    return m_pStateMachine;
}

void Game::initStateMachine() {
    m_pStateMachine = new GameStateMachine();
    m_pStateMachine->pushState(new MainMenuState());
}

void Game::initGameObjects() {
    TheGameObjectFactory::Instance()->registerType("TextObject",
            new TextObjectCreator());
    TheGameObjectFactory::Instance()->registerType("MenuButton",
            new MenuButtonCreator());
}

