#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "LoaderParams.hpp"
#include "GameObjectFactory.hpp"

class GameObject {
    public:
        virtual void render() = 0;
        virtual void update(unsigned int deltaTime) = 0;
        virtual void clean() = 0;
        virtual void load(const LoaderParams *pParams) = 0;

    protected:
        GameObject() {}
        virtual ~GameObject() {}

};

#endif

