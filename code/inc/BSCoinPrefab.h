#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <FSConverter.h>
#include <EngineBravo.h>

class BSCoinPrefab {
public:
    BSCoinPrefab();
    GameObject* createBSCoinPrefab();
private:
    int mCoinWidth;
    int mCoinHeight;
    Vector2 mCoinSpritePosition;
    SpriteDef mCoinSpriteDef;

    void addSprite(GameObject* gameObject);
};