#include "StateParser.hpp"

bool StateParser::parseState(const char* stateFile, std::string stateID,
        std::vector<GameObject*> *pObjects,
        std::vector<std::string> *pTextureIDs) {
    return false;

}

void StateParser::parseObjects(Json* pStateRoot,
        std::vector<GameObject*> *pObjects) {

}

void StateParser::parseTextures(Json* pStateRoot,
        std::vector<std::string> *pTextureIDs) {

}
