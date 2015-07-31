#ifndef __PLAYER__
#define __PLAYER__

#include "GameObject.hpp"
#include "Vector2D.hpp"

class Player : public GameObject {
    public:
        Player();

        virtual void render() {};
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);

        Vector2D getPosition() const { return m_position; }
        double getDirX() const { return m_dirX; }
        double getDirY() const { return m_dirY; }

        void alterPosition(const double x, const double y);
        void setDirX(const double dir) { m_dirX = dir; }
        void setDirY(const double dir) { m_dirY = dir; }

    protected:

        double m_dirX;
        double m_dirY;

        Vector2D m_position;
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif
