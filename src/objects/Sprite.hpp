#ifndef __SPRITE__
#define __SPRITE__

#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include <string>

class Sprite : public GameObject {
    public:
        Sprite();
        virtual ~Sprite();
        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams *pParams);

        Vector2D& getPosition() { return m_position; }
        std::string getTextureID() const { return m_textureID; };

    private:
        Vector2D m_position;
        std::string m_textureID;

};

class SpriteCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Sprite();
    }
};

#endif
