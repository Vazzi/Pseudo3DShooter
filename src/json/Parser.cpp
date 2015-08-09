#include "Parser.hpp"

#include <fstream>
#include "../managers/TextureManager.hpp"
#include "../managers/SurfaceManager.hpp"
#include "../managers/FontManager.hpp"
#include "../objects/GameObject.hpp"
#include "../Game.hpp"

Json Parser::getRoot(const char* stateFile) {
    std::ifstream ifs;
    ifs.open(stateFile, std::ifstream::in);
    if (ifs.fail()) {
        std::cerr << "Error: " << strerror(errno);
        return nullptr;
    }
    string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    string err;
    Json root = Json::parse(content, err);
    if (root == nullptr) {
        std::cerr << err;
    }

    return root;
}

void Parser::parseObjects(Json* pRoot, vector<GameObject*> *pObjects) {
    vector<Json> textures = (*pRoot)["objects"].array_items();

    for (vector<Json>::iterator it = textures.begin(); it != textures.end(); ++it) {
        GameObject* pObject = createObjectFromJson(&(*it));
        setupObject(&(*it), pObject);
        pObjects->push_back(pObject);
    }
}

void Parser::parseTextures(Json* pRoot, vector<string> *pTextureIDs,
        bool bSurface) {
    vector<Json> textures = (*pRoot)["textures"].array_items();

    for (vector<Json>::iterator it = textures.begin(); it != textures.end(); ++it) {
        string fileName = (*it)["fileName"].string_value();
        string textureId = (*it)["id"].string_value();

        pTextureIDs->push_back(textureId);
        if (bSurface) {
            TheSurfaceManager::Instance()->load(fileName, textureId);
        } else {
            TheTextureManager::Instance()->load(fileName, textureId,
                    TheGame::Instance()->getRenderer());
        }
    }
}

void Parser::parseFonts(Json* pRoot, vector<string> *pFontIDs) {
    vector<Json> fonts = (*pRoot)["fonts"].array_items();

    for (vector<Json>::iterator it = fonts.begin(); it != fonts.end(); ++it) {
        string fileName = (*it)["fileName"].string_value();
        string fontId = (*it)["id"].string_value();
        int letterWidth = (*it)["letterWidth"].int_value();
        int letterHeight = (*it)["letterHeight"].int_value();

        pFontIDs->push_back(fontId);
        TheFontManager::Instance()->load(fileName, fontId, letterWidth,
                letterHeight, TheGame::Instance()->getRenderer());
    }
}

GameObject* Parser::createObjectFromJson(Json* pJsonObject) {
    double x = (*pJsonObject)["x"].number_value();
    double y = (*pJsonObject)["y"].number_value();
    int width = (*pJsonObject)["width"].int_value();
    int height = (*pJsonObject)["height"].int_value();
    int callbackId = (*pJsonObject)["callbackId"].int_value();
    string textureId = (*pJsonObject)["textureId"].string_value();
    string type = (*pJsonObject)["type"].string_value();

    GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);
    pGameObject->load(new LoaderParams(x, y, width, height, textureId, callbackId));

    return pGameObject;
}
