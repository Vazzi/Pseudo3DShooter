#ifndef __WORLD_PARSER__
#define __WORLD_PARSER__

#include "Parser.hpp"

class Map;
class Player;

class WorldParser : public Parser {
    public:
        bool parseWorld(const char* file,
                vector<GameObject*>* pObjects,
                Map** pMap, Player** pPlayer,
                vector<string>* pSurfaces);
    private:
        void parseMap(Json* pRoot, Map** pMap);
        void setupPlayer(Json* pJsonObject, GameObject* pObject);
        virtual void setupObject(Json* pJsonObject, GameObject* pObject);

};
#endif
