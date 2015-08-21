#ifndef __WORLD_PARSER__
#define __WORLD_PARSER__

#include "Parser.hpp"

class Map;
class Sprite;

class WorldParser : public Parser {
    public:
        bool parseWorld(const char* file,
                vector<Sprite*>* pSprites,
                Map** pMap,
                vector<string>* pSurfaces);
    private:
        void parseMap(Json* pRoot, Map** pMap);
        void setupPlayer(Json* pJsonObject);
        virtual void setupSprite(Json* pJsonObject, Sprite* pObject);
        void parseSprites(Json* pRoot, vector<Sprite*> *pObjects);
        virtual void setupObject(Json* pJsonObject, GameObject* pObject);

};
#endif
