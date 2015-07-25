#include "StateParser.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "../TextureManager.hpp"
#include "../objects/GameObjectFactory.hpp"
#include "../objects/GameObject.hpp"
#include "../objects/LoaderParams.hpp"
#include "../objects/TextObject.hpp"
#include "../Game.hpp"

bool StateParser::parseState(const char* stateFile, std::string stateID,
        std::vector<GameObject*>* pObjects,
        std::vector<std::string>* pTextureIDs,
        std::vector<std::string>* pFontIDs) {

    Json root = getRoot(stateFile);
    if (root == nullptr) {
        return false;
    }

    std::vector<Json> states = root.array_items();
    Json* pStateNode = nullptr;
    for (std::vector<Json>::iterator it = states.begin();
            it != states.end(); ++it) {
        if ((*it)["stateId"].string_value() == stateID) {
            pStateNode = &(*it);
            break;
        }
    }

    parseFonts(pStateNode, pFontIDs);
    parseTextures(pStateNode, pTextureIDs);
    parseObjects(pStateNode, pObjects);

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
    std::vector<Json> textures = (*pStateRoot)["objects"].array_items();
    for (std::vector<Json>::iterator it = textures.begin();
            it != textures.end(); ++it) {
        GameObject* pObject = createObjectFromJson(&(*it));
        setupObject(&(*it), pObject);
        pObjects->push_back(pObject);
    }
}

GameObject* StateParser::createObjectFromJson(Json* pJsonObject) {
    int x = (*pJsonObject)["x"].int_value();
    int y = (*pJsonObject)["y"].int_value();
    int width = (*pJsonObject)["width"].int_value();
    int height = (*pJsonObject)["height"].int_value();
    int callbackId = (*pJsonObject)["callbackId"].int_value();
    std::string textureId = (*pJsonObject)["textureId"].string_value();
    std::string type = (*pJsonObject)["type"].string_value();

    GameObject* pGameObject = TheGameObjectFactory::Instance()->create(type);
    pGameObject->load(new LoaderParams (x, y, width, height, textureId, callbackId));

    return pGameObject;
}

void StateParser::setupObject(Json* pJsonObject, GameObject* pObject) {
    std::string type = (*pJsonObject)["type"].string_value();

    if (type == "TextObject") {
        setupTextObject(pJsonObject, pObject);
    } else if (type == "MenuButton") {
        setupMenuButton(pJsonObject, pObject);
    }
}

void StateParser::setupTextObject(Json* pJsonObject, GameObject* pObject) {
    TextObject* pTextObject = (TextObject *)pObject;
    std::string text = (*pJsonObject)["text"].string_value();
    pTextObject->setText(text);

    int scale = (*pJsonObject)["scale"].int_value();
    if (scale) {
        pTextObject->setScale(scale);
    }
    int spacing = (*pJsonObject)["spacing"].int_value();
    if (spacing) {
        pTextObject->setSpacing(spacing);
    }
    Json colorData = (*pJsonObject)["color"];
    if (!colorData.is_null())  {
        Json color = colorData.object_items();
        int r = color["r"].int_value();
        int g = color["g"].int_value();
        int b = color["b"].int_value();
        pTextObject->setColor(r, g, b);
    }
    Json flashColorData = (*pJsonObject)["colorFlash"];
    if (!flashColorData.is_null())  {
        Json flashColor = flashColorData.object_items();
        int r = flashColor["r"].int_value();
        int g = flashColor["g"].int_value();
        int b = flashColor["b"].int_value();
        int rate = flashColor["rate"].int_value();
        pTextObject->setColorFlash(r, g, b, rate);
    }

}

void StateParser::setupMenuButton(Json* pJsonObject, GameObject* pObject) {
    setupTextObject(pJsonObject, pObject);
}

void StateParser::parseTextures(Json* pStateRoot,
        std::vector<std::string> *pTextureIDs) {
    std::vector<Json> textures = (*pStateRoot)["textures"].array_items();
    for (std::vector<Json>::iterator it = textures.begin();
            it != textures.end(); ++it) {
        std::string fileName = (*it)["fileName"].string_value();
        std::string textureId = (*it)["id"].string_value();
        pTextureIDs->push_back(textureId);
        TheTextureManager::Instance()->load(fileName, textureId,
                TheGame::Instance()->getRenderer());
    }
}

void StateParser::parseFonts(Json* pStateRoot,
        std::vector<std::string> *pFontIDs) {
    std::vector<Json> fonts = (*pStateRoot)["fonts"].array_items();
    for (std::vector<Json>::iterator it = fonts.begin();
            it != fonts.end(); ++it) {
        std::string fileName = (*it)["fileName"].string_value();
        std::string fontId = (*it)["id"].string_value();
        int letterWidth = (*it)["letterWidth"].int_value();
        int letterHeight = (*it)["letterHeight"].int_value();
        pFontIDs->push_back(fontId);
        TheFontManager::Instance()->load(fileName, fontId, letterWidth,
                letterHeight, TheGame::Instance()->getRenderer());
    }
}
