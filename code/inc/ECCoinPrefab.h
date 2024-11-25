#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <FSConverter.h>
#include <EngineBravo.h>

class ECCoinPrefab {
public:
    ECCoinPrefab();
    GameObject* createECCoinPrefab();
private:
    int mCoinWidth;
    int mCoinHeight;
    Vector2 mCoinSpritePosition;
    SpriteDef mCoinSpriteDef;

    void addSprite(GameObject* gameObject);
};