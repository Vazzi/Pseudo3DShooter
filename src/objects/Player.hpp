#ifndef __PLAYER__
#define __PLAYER__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"

class Player : public GameObject {
    public:
        static Player* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new Player();
            }
            return s_pInstance;
        }

        virtual void render() {};
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);

        Vector2D getPosition() const { return m_position; }
        double getDirX() const { return m_dirX; }
        double getDirY() const { return m_dirY; }
        double getPlaneX() const { return m_planeX; }
        double getPlaneY() const { return m_planeY; }
        void alterPosition(const double x, const double y);
        void setDirX(const double dir) { m_dirX = dir; }
        void setDirY(const double dir) { m_dirY = dir; }
        void moveSteps(int x, int y);
        double nextStepX(bool back = false);
        double nextStepY(bool back = false);
        void rotateLeft();
        void rotateRight();
        int getHealth() const { return m_health; };
        void hit(int damage);

    protected:
        Player();
        ~Player();

        static Player* s_pInstance;

        double m_dirX;
        double m_dirY;
        double m_moveSpeed;
        double m_rotSpeed;
        double m_planeX;
        double m_planeY;
        int m_health;

        Vector2D m_position;

        void rotate(int sign = 1);
};

typedef Player ThePlayer;

#endif
