#ifndef __STATE_PARSER__
#define __STATE_PARSER__

#include "Parser.hpp"

class StateParser : public Parser {
    public:
        bool parseState(const char* stateFile, string stateID,
                vector<GameObject*>* pObjects,
                vector<string>* pTextureIDs,
                vector<string>* pFontIDs);
    private:
        virtual void setupObject(Json* pJsonObject, GameObject* pObject);
        void setupTextObject(Json* pJsonObject, GameObject* pObject);
        void setupMenuButton(Json* pJsonObject, GameObject* pObject);
        void setupWorld(Json* pJsonObject, GameObject* pObject);
};

#endif

