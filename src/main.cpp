#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"
#include <iostream>

unsigned int g_outputTimer = 0;
unsigned int g_framePerSeconds = 0;
unsigned int g_lastTime = 0;

void printFPS(unsigned int currentTime) {
    if (currentTime > g_outputTimer) {
        std::cout << "FPS: " << g_framePerSeconds << std::endl;
        g_framePerSeconds = 0;
        g_outputTimer += 1000;
    }
}

unsigned int getDeltaTime(unsigned int currentTime) {
    unsigned int deltaTime = (currentTime - g_lastTime);
    g_lastTime = currentTime;
    return deltaTime;
}

void gameLoop() {
    unsigned int currentTime;

    while (TheGame::Instance()->running()) {
        currentTime = SDL_GetTicks();
        printFPS(currentTime);

        unsigned int deltaTime = getDeltaTime(currentTime);
        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update(deltaTime);
        TheGame::Instance()->render();
        g_framePerSeconds++;
        SDL_Delay(1);
    }
}

int main(int argc, char *argv[]) {

    std::cout << "game init attempt...\n";
    if (TheGame::Instance()->init()) {
        std::cout << "game init success!\n";
        gameLoop();
    } else {
        std::cout << "game init failure - " << SDL_GetError() << std::endl;
        return -1;
    }
    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}
