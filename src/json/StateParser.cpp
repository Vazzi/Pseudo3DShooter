#include "StateParser.hpp"
#include <string>
#include <vector>
#include <iostream>

#include "../TextureManager.hpp"
#include "../SurfaceManager.hpp"
#include "../objects/GameObjectFactory.hpp"
#include "../objects/GameObject.hpp"
#include "../objects/LoaderParams.hpp"
#include "../objects/TextObject.hpp"
#include "../objects/World.hpp"
#include "../objects/Player.hpp"
#include "../objects/Map.hpp"
#include "../Game.hpp"

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

bool StateParser::parseWorld(const char* file, vector<GameObject*>* pObjects,
        Map** pMap, Player** pPlayer, vector<string>* pSurfaces) {
    Json root = getRoot(file);
    if (root == nullptr) {
        return false;
    }
    parseObjects(&root, pObjects);
    parseMap(&root, pMap);
    parseTextures(&root, pSurfaces, true);
    Json playerData = root["player"].object_items();
    *pPlayer = (Player*)createObjectFromJson(&playerData);
    setupPlayer(&playerData, *pPlayer);
    return true;
}


void StateParser::parseMap(Json* pRoot, Map** pMap) {
    Json mapObject = (*pRoot)["map"].object_items();

    int width = mapObject["width"].int_value();
    int height = mapObject["height"].int_value();
    vector<Json> data = mapObject["data"].array_items();
    vector<Json> walls = mapObject["walls"].array_items();
    string ceiling = mapObject["ceiling"].string_value();
    string floor = mapObject["floor"].string_value();

    int mapArray[width * height];

    for (int y = 0; y < height; y++) {
        vector<Json> line = data[y].array_items();
        for (int x = 0; x < width; x++) {
            mapArray[x + (y * width)] = line[x].int_value();
        }
    }

    *pMap = new Map(width, height);
    (*pMap)->loadMap(mapArray);
    (*pMap)->setFloorID(floor);
    (*pMap)->setCeilingID(ceiling);
    for (unsigned int i = 0; i < walls.size(); i++) {
        (*pMap)->addWall(walls[i].string_value());
    }

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

void StateParser::setupPlayer(Json* pJsonObject, GameObject* pObject) {
    Player* pPlayer = (Player *)pObject;
    double dirX = (*pJsonObject)["dirX"].number_value();
    double dirY = (*pJsonObject)["dirY"].number_value();
    pPlayer->setDirX(dirX);
    pPlayer->setDirY(dirY);
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
