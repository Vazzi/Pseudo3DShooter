#include "StateParser.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

bool StateParser::parseState(const char* stateFile, std::string stateID,
        std::vector<GameObject*> *pObjects,
        std::vector<std::string> *pTextureIDs) {

    Json root = getRoot(stateFile);
    if (root == nullptr) {
        return false;
    }

    std::vector<Json> states = root.array_items();
    Json *stateNode = nullptr;
    for (std::vector<Json>::iterator it = states.begin();
            it != states.end(); ++it) {
        if ((*it)["stateId"].string_value() == stateID) {
            stateNode = &(*it);
            break;
        }
    }

    parseTextures(stateNode, pTextureIDs);
    parseObjects(stateNode, pObjects);

    return true;

}

Json StateParser::getRoot(const char* stateFile) {
    std::ifstream ifs;
    ifs.open(stateFile, std::ifstream::in);
    if (ifs.fail()) {
        std::cerr << "Error: " << strerror(errno);
        return nullptr;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    std::string err;
    Json root = Json::parse(content, err);
    if (root == nullptr) {
        std::cerr << err;
    }

    return root;
}

void StateParser::parseObjects(Json* pStateRoot,
        std::vector<GameObject*> *pObjects) {

}

void StateParser::parseTextures(Json* pStateRoot,
        std::vector<std::string> *pTextureIDs) {

}
