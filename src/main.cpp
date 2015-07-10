#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"

Uint32 g_outputTimer = 0;
Uint32 g_framePerSeconds = 0;
Uint32 g_lastTime = 0;

void printFPS(Uint32 currentTime) {
    if (currentTime > g_outputTimer) {
        std::cout << "FPS: " << g_framePerSeconds << std::endl;
        g_framePerSeconds = 0;
        g_outputTimer += 1000;
    }
}

Uint32 getDeltaTime(Uint32 currentTime) {
    Uint32 deltaTime = (currentTime - g_lastTime);
    g_lastTime = currentTime;
    return deltaTime;
}

void gameLoop() {
    Uint32 frameStart;

    while (TheGame::Instance()->running()) {
        frameStart = SDL_GetTicks();
        printFPS(frameStart);

        Uint32 deltaTime = SDL_GetTicks() - frameStart;
        TheGame::Instance()->handleEvents(deltaTime);
        TheGame::Instance()->update(deltaTime);
        TheGame::Instance()->render(deltaTime);
        g_framePerSeconds++;
        SDL_Delay(2);
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
