#ifndef __HEALTH_STATUS__
#define __HEALTH_STATUS__

#include "TextObject.hpp"

class HealthStatus : public TextObject {
public:
    virtual void update(unsigned int deltaTime);
};

class HealthStatusCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new HealthStatus();
    }
};

#endif
