#ifndef __PARSER__
#define __PARSER__

#include "json11.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using json11::Json;

class GameObject;

class Parser {
    protected:
        Json getRoot(const char* stateFile);
        GameObject* createObjectFromJson(Json* pJsonObject);
        void parseObjects(Json* pStateRoot,
                vector<GameObject*> *pObjects);
        void parseTextures(Json* pStateRoot,
                vector<string> *pTextureIDs, bool bSurface = false);
        void parseFonts(Json* pStateRoot,
                vector<string> *pFontIDs);
        virtual void setupObject(Json* pJsonObject, GameObject* pObject) = 0;
};

#endif
