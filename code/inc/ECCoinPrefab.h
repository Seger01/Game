#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <FSConverter.h>
#include <EngineBravo.h>
#include <CircleCollider.h>
#include <RigidBody.h>


class ECCoinPrefab {
public:
    ECCoinPrefab();
    GameObject* createECCoinPrefab(GameObject& objDroppingCoin);
private:
    int mCoinWidth;
    int mCoinHeight;
    Vector2 mCoinSpritePosition;
    SpriteDef mCoinSpriteDef;

    void addSprite(GameObject* gameObject);
    void addRigidBody(GameObject* gameObject);
    void addCollider(GameObject* gameObject);
    void setTransform(GameObject* gameObject, Transform objDroppingCoinTransform);
};