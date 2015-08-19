#ifndef __ANIMATED_OBJECT__
#define __ANIMATED_OBJECT__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include <string>

using std::string;

class AnimatedObject : public GameObject {
    public:
        AnimatedObject();

        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);

        Vector2D& getPosition() { return m_position; }
        int getWidth() { return m_width; }
        int getHeight() { return m_height; }

    protected:
        int m_width;
        int m_height;
        Vector2D m_position;
        string m_textureID;

        int m_currentFrame;
        int m_currentRow;
        int m_numFrames;
        float m_scale;

        int m_animTime;
        int m_animSpeed;
        bool m_isAnimating;
};

class AnimatedObjectCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new AnimatedObject();
    }
};

#endif
