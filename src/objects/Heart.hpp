#ifndef __HEART__
#define __HEART__

#include "AnimatedObject.hpp"

class Heart : public AnimatedObject {
    public:
        void update(unsigned int deltaTime);
};

class HeartCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Heart();
    }
};

#endif
