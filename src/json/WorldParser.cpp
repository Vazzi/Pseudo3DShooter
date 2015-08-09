#include "WorldParser.hpp"

#include "../objects/Player.hpp"
#include "../objects/Map.hpp"

bool WorldParser::parseWorld(const char* file, vector<GameObject*>* pObjects,
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

void WorldParser::setupPlayer(Json* pJsonObject, GameObject* pObject) {
    Player* pPlayer = (Player *)pObject;
    double dirX = (*pJsonObject)["dirX"].number_value();
    double dirY = (*pJsonObject)["dirY"].number_value();
    pPlayer->setDirX(dirX);
    pPlayer->setDirY(dirY);
}

void WorldParser::parseMap(Json* pRoot, Map** pMap) {
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

void WorldParser::setupObject(Json* pJsonObject, GameObject* pObject) {
    // empty
}
