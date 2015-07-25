#ifndef __STATE_PARSER__
#define __STATE_PARSER__

#include <iostream>
#include <vector>
#include "json11.hpp"

class GameObject;
using json11::Json;

class StateParser {
    public:
        bool parseState(const char* stateFile, std::string stateID,
                std::vector<GameObject*>* pObjects,
                std::vector<std::string>* pTextureIDs,
                std::vector<std::string>* pFontIDs);
    private:
        void parseObjects(Json* pStateRoot,
                std::vector<GameObject*> *pObjects);
        void parseTextures(Json* pStateRoot,
                std::vector<std::string> *pTextureIDs);
        void parseFonts(Json* pStateRoot,
                std::vector<std::string> *pFontIDs);
        Json getRoot(const char* stateFile);
        GameObject* createObjectFromJson(Json* pJsonObject);
        void setupObject(Json* pJsonObject, GameObject* pObject);
        void setupTextObject(Json* pJsonObject, GameObject* pObject);
        void setupMenuButton(Json* pJsonObject, GameObject* pObject);
};
#endif

