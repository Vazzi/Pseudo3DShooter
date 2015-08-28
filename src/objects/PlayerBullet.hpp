#ifndef __PLAYER_BULLET__
#define __PLAYER_BULLET__

#include "Sprite.hpp"

class PlayerBullet : public Sprite {
    public:
        PlayerBullet();

        virtual ~PlayerBullet ();
        virtual std::string type() { return "PlayerBullet"; }
        virtual void load(LoaderParams* pParams, Vector2D heading);
        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
    private:
        Vector2D m_heading;

};

#endif
