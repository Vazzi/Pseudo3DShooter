#ifndef __STATIC_OBJECT__
#define __STATIC_OBJECT__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include <string>

class StaticObject : public GameObject {
    public:
        StaticObject();
        virtual ~StaticObject();
        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams *pParams);

        Vector2D& getPosition() { return m_position; }
        int getWidth() { return m_width; }
        int getHeight() { return m_height; }

    private:
        int m_width;
        int m_height;
        Vector2D m_position;
        std::string m_textureID;

};

class StaticObjectCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new StaticObject();
    }
};

#endif
