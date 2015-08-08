#ifndef __RAY__
#define __RAY__

class Player;
class Map;

class Ray {
    public:
        Ray(int x, double width, Player* pPlayer);

        double getX() const { return m_posX; }
        double getY() const { return m_posY; }
        double getDirX() const { return m_dirX; }
        double getDirY() const { return m_dirY; }
        int getMapX() const { return m_mapX; }
        int getMapY() const { return m_mapY; }
        double getDeltaDistX() const { return m_deltaDistX; }
        double getDeltaDistY() const { return m_deltaDistY; }
        void makeStepX() { m_mapX += m_stepX; }
        void makeStepY() { m_mapY += m_stepY; }
        int getSide() const { return m_side; }

        void performDDA(Map* pMap);
        double getWallDist() const;
        double getWallX() const;


    private:
        double m_posX;
        double m_posY;
        double m_dirX;
        double m_dirY;
        int m_mapX;
        int m_mapY;
        double m_deltaDistX;
        double m_deltaDistY;
        // Length of ray from current position to next x or y-side
        double m_sideDistX;
        double m_sideDistY;
        // What direction to step in x or y-direction (either +1 or -1)
        int m_stepX;
        int m_stepY;
        // If wall was hit on X(NS) or Y(WE) side
        int m_side;

        double m_wallDist;

        void setStepAndSideDist();

};

#endif
