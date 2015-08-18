#ifndef __GAME_SURFACE__
#define __GAME_SURFACE__

#include <SDL2/SDL_image.h>

class GameSurface {
public:
    GameSurface(unsigned int width, unsigned int height);
    ~GameSurface();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void putPixel(int x, int y, Uint32 pixel);
    void draw(int x, int y, int width, int height);
    void clear();

private:
    SDL_Surface* m_pSurface;
    Uint32* m_pBuffer;
    int m_width;
    int m_height;

    void drawSurface(int x, int y, int width, int height);
    void bufferToSurface();
};

#endif
