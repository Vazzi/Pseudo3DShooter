#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>

class GameStateMachine;

class Game {
    public:
        static Game* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new Game();
                return s_pInstance;
            }
            return s_pInstance;
        }

        bool init();
        void render(Uint32 deltaTime);
        void update(Uint32 deltaTime);
        void handleEvents(Uint32 deltaTime);
        void clean();
        void quit();
        bool running();
        GameStateMachine* getStateMachine();

    private:
        Game();

        static Game* s_pInstance;

        bool m_isRunning;
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        GameStateMachine* m_pStateMachine;

        bool initWindow(const char* title, int xpos, int ypos, int height,
                int width, bool fullscreen);
        bool initRenderer();
        void initStateMachine();

};

typedef Game TheGame;

#endif
