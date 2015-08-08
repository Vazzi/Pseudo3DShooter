#ifndef __MAP__
#define __MAP__

#include <vector>
#include <string>

using std::string;

class Map {
    public:
        Map(const int width , const int height);
        ~Map ();
        void loadMap(int array[]);
        void setWallID(const string id) { m_walls.push_back(id); };
        void setFloorID(const string id) { m_floorID = id; };
        void setCeilingID(const string id) { m_ceilingID = id; };
        string getWallTextureID(const unsigned int x, const unsigned int y) const;
        string getFloorTextureID() const { return m_floorID; };
        string getCeilingTextureID() const { return m_ceilingID; };
        bool isEmpty(const unsigned int x, const unsigned int y);
        bool isWall(const unsigned int x, const unsigned int y);

    private:
        int* m_map;
        std::vector<string> m_walls;
        string m_floorID;
        string m_ceilingID;
        unsigned int m_width;
        unsigned int m_height;
};

#endif
