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
        void render();
        void update(unsigned int deltaTime);
        void handleEvents();
        void clean();
        void quit();
        int getHeight() const { return m_height; }
        int getWidth() const { return m_width; }
        bool running();
        SDL_Renderer* getRenderer() const { return m_pRenderer; }
        GameStateMachine* getStateMachine();

    private:
        Game();

        static Game* s_pInstance;

        bool m_isRunning;
        int m_width;
        int m_height;
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        GameStateMachine* m_pStateMachine;

        bool initWindow(const char* title, int xpos, int ypos, int height,
                int width, bool fullscreen);
        bool initRenderer();
        void initStateMachine();
        void initGameObjects();


};

typedef Game TheGame;

#endif
