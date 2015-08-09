#ifndef __STATE_PARSER__
#define __STATE_PARSER__

#include "Parser.hpp"

class Map;
class Player;

class StateParser : public Parser {
    public:
        bool parseState(const char* stateFile, string stateID,
                vector<GameObject*>* pObjects,
                vector<string>* pTextureIDs,
                vector<string>* pFontIDs);
        bool parseWorld(const char* file,
                vector<GameObject*>* pObjects,
                Map** pMap, Player** pPlayer,
                vector<string>* pSurfaces);
    private:
        void parseMap(Json* pRoot, Map** pMap);
        virtual void setupObject(Json* pJsonObject, GameObject* pObject);
        void setupTextObject(Json* pJsonObject, GameObject* pObject);
        void setupMenuButton(Json* pJsonObject, GameObject* pObject);
        void setupPlayer(Json* pJsonObject, GameObject* pObject);
        void setupWorld(Json* pJsonObject, GameObject* pObject);
};
#endif

