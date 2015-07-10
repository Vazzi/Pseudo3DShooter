#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>

class Game {
    public:
        static Game* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new Game();
                return s_pInstance;
            }
            return s_pInstance;
        }

        bool init(const char* title, int xpos, int ypos, int height,
                int width, bool fullscreen);
        void render(Uint32 deltaTime);
        void update(Uint32 deltaTime);
        void handleEvents(Uint32 deltaTime);
        void clean();
        void quit();
        bool running();

    private:
        Game();

        static Game* s_pInstance;

        bool m_isRunning;

};

typedef Game TheGame;

#endif
