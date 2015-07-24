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
                std::vector<GameObject*> *pObjects,
                std::vector<std::string> *pTextureIDs);
    private:
        void parseObjects(Json* pStateRoot,
                std::vector<GameObject*> *pObjects);
        void parseTextures(Json* pStateRoot,
                std::vector<std::string> *pTextureIDs);
};
#endif

