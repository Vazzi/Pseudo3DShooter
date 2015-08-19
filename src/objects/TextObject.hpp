#ifndef __TEXT_OBJECT__
#define __TEXT_OBJECT__

#include <string>
#include "GameObject.hpp"
#include "../utility/Vector2D.hpp"
#include "../managers/FontManager.hpp"

class TextObject : public GameObject {
    public:
        TextObject();

        virtual void render();
        virtual void update(unsigned int deltaTime);
        virtual void clean();
        virtual void load(const LoaderParams* pParams);

        Vector2D& getPosition() { return m_position; }
        int getWidth() { return m_width; }
        int getHeight() { return m_height; }
        void setText(std::string text) { m_text = text; }
        void setSpacing(int spacing) { m_spacing = spacing; }
        void setColor(int r, int g, int b);
        void setColorFlash(int r, int g, int b, unsigned int rate);

    protected:
        int m_width;
        int m_height;
        std::string m_fontID;
        std::string m_text;
        Vector2D m_position;
        float m_scale;
        int m_spacing;
        FontColor m_color;
        FontColor m_flashColor;
        int m_flashTime;
        unsigned int m_flashRate;
        int m_currentColorIndex;

        void renderFontWithColor(FontColor color);

};

class TextObjectCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new TextObject();
    }
};

#endif

