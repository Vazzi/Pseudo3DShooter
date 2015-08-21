#include "WorldParser.hpp"

#include "../objects/Player.hpp"
#include "../objects/Map.hpp"
#include "../objects/Sprite.hpp"

bool WorldParser::parseWorld(const char* file, vector<Sprite*>* pObjects,
        Map** pMap, vector<string>* pSurfaces) {
    Json root = getRoot(file);
    if (root == nullptr) {
        return false;
    }
    parseSprites(&root, pObjects);
    parseMap(&root, pMap);
    parseTextures(&root, pSurfaces, true);
    Json playerData = root["player"].object_items();
    setupPlayer(&playerData);
    return true;
}

void WorldParser::setupPlayer(Json* pJsonObject) {
    double x = (*pJsonObject)["x"].number_value();
    double y = (*pJsonObject)["y"].number_value();
    double dirX = (*pJsonObject)["dirX"].number_value();
    double dirY = (*pJsonObject)["dirY"].number_value();
    ThePlayer::Instance()->load(new LoaderParams(x, y, 0, 0, ""));
    ThePlayer::Instance()->setDirX(dirX);
    ThePlayer::Instance()->setDirY(dirY);
}

void WorldParser::parseSprites(Json* pRoot, vector<Sprite*> *pObjects) {
    vector<Json> textures = (*pRoot)["objects"].array_items();

    for (vector<Json>::iterator it = textures.begin(); it != textures.end(); ++it) {
        Sprite* pObject = (Sprite*)createObjectFromJson(&(*it));
        setupSprite(&(*it), pObject);
        pObjects->push_back(pObject);
    }
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

void WorldParser::setupSprite(Json* pJsonObject, Sprite* pObject) {
    int isSolid = (*pJsonObject)["solid"].int_value();
    pObject->setSolid(isSolid);
}

void WorldParser::setupObject(Json* pJsonObject, GameObject* pObject) {
    // empty
}
