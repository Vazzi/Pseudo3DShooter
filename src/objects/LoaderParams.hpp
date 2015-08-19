#ifndef __LOADER_PARAMS__
#define __LOADER_PARAMS__

#include <string>

class LoaderParams {
    public:
        LoaderParams(double x, double y, int width, int height, std::string
                textureID, int callbackID = 0, float scale = 1, int numFrames = 1,
                int animSpeed = 0) :
            m_x(x),
            m_y(y),
            m_width(width),
            m_height(height),
            m_textureID(textureID),
            m_numFrames(numFrames),
            m_callbackID(callbackID),
            m_scale(scale),
            m_animSpeed(animSpeed) {}
        double getX() const { return m_x; }
        double getY() const { return m_y; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getNumFrames() const { return m_numFrames; }
        int getAnimSpeed() const { return m_animSpeed; }
        int getCallbackID() const { return m_callbackID; }
        float getScale() const { return m_scale; }
        std::string getTextureID() const { return m_textureID; }

    private:
        double m_x;
        double m_y;
        int m_width;
        int m_height;
        std::string m_textureID;
        int m_numFrames;
        int m_callbackID;
        int m_animSpeed;
        float m_scale;

};

#endif
