#include "StateParser.hpp"

#include "../objects/TextObject.hpp"
#include "../objects/World.hpp"

bool StateParser::parseState(const char* stateFile, string stateID,
        vector<GameObject*>* pObjects,
        vector<string>* pTextureIDs,
        vector<string>* pFontIDs) {

    Json root = getRoot(stateFile);
    if (root == nullptr) {
        return false;
    }

    vector<Json> states = root.array_items();
    Json* pStateNode = nullptr;
    for (vector<Json>::iterator it = states.begin();
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

void StateParser::setupObject(Json* pJsonObject, GameObject* pObject) {
    string type = (*pJsonObject)["type"].string_value();

    if (type == "TextObject") {
        setupTextObject(pJsonObject, pObject);
    } else if (type == "MenuButton") {
        setupMenuButton(pJsonObject, pObject);
    } else if (type == "World") {
        setupWorld(pJsonObject, pObject);
    }
}

void StateParser::setupWorld(Json* pJsonObject, GameObject* pObject) {
    World* pWorld = (World *)pObject;
    string levelFile = (*pJsonObject)["sourceFile"].string_value();
    pWorld->loadLevelData(levelFile);
}

void StateParser::setupTextObject(Json* pJsonObject, GameObject* pObject) {
    TextObject* pTextObject = (TextObject *)pObject;
    string text = (*pJsonObject)["text"].string_value();
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
