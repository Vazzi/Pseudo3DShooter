#ifndef __INPUT_HANLDE__
#define __INPUT_HANLDE__

#include <SDL2/SDL.h>

class InputHandler {
public:
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void update();
    void clean();
    bool isKeyDown(SDL_Scancode key) const;

private:
    const Uint8* m_keystates;

    InputHandler();
    ~InputHandler() {};

    static InputHandler* s_pInstance;

    void onKeyDown();
    void onKeyUp();

};

typedef InputHandler TheInputHandler;

#endif
