#include "CollisionManager.hpp"

#include "../objects/Sprite.hpp"

bool CollisionManager::collide(int x, int y, const vector<Sprite*> &objects) {
    for (vector<Sprite*>::const_iterator it = objects.begin();
            it < objects.end(); ++it) {
        Sprite* pSprite = (*it);

        if (!pSprite->isSolid()) {
            continue;
        }

        int spriteTileX = std::floor(pSprite->getPosition().getX());
        int spriteTileY = std::floor(pSprite->getPosition().getY());

        if (spriteTileX == x && spriteTileY == y) {
            return true;
        }

    }
    return false;
}
