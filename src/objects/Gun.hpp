#ifndef __GUN__
#define __GUN__

#include "AnimatedObject.hpp"

class Gun : public AnimatedObject {
public:
    Gun();

    void update(unsigned int deltaTime);

private:
    bool m_isShooting;

};

class GunCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Gun();
    }
};

#endif
