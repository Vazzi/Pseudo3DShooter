#ifndef __WORLD_OBJECT__
#define __WORLD_OBJECT__

#include "GameObject.hpp"
#include "Vector2D.hpp"

class WorldObject : public GameObject {
    public:
        WorldObject();

        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);
    private:
        double m_posX;
        double m_posY;
        double m_dirX;
        double m_dirY;
        double m_planeX;
        double m_planeY;
        double m_time;
        double m_oldTime;
        int m_keyTime;

};

#endif
