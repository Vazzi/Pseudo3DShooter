#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

#include <vector>

using std::vector;

class Sprite;

class CollisionManager {
    public:
        static bool collide(int x, int y, const vector<Sprite*> &objects);

};


#endif
