#ifndef __BULLET_HANDLER__
#define __BULLET_HANDLER__

#include <string>
#include <vector>
#include "../utility/Vector2D.hpp"

using std::string;

class BulletHandler {
    public:
        static BulletHandler* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new BulletHandler();
            }
        }

        void addPlayerBullet(int x, int y, int width, int height, string textureID,
                int numFrames, Vector2D heading);
        void update(unsigned int deltaTime);
        void render();

    private:
        BulletHandler();
        ~BulletHandler();

        static BulletHandler* s_pInstance;

        std::vector<PlayerBullet*> m_playerBullets;

};
#endif
