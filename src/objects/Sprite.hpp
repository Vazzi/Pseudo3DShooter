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
        std::string getTextureID() const { return m_textureID; }
        bool isSolid() const { return m_isSolid; }
        void setSolid(bool isSolid) { m_isSolid = isSolid; }

    private:
        Vector2D m_position;
        std::string m_textureID;
        bool m_isSolid;

};

class SpriteCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Sprite();
    }
};

#endif
