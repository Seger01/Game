#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <FSConverter.h>
#include <EngineBravo.h>
#include <CircleCollider.h>
#include <RigidBody.h>
#include "BSCoinBehaviourScript.h"

class BSCoinPrefab {
public:
    BSCoinPrefab();
    GameObject* createBSCoinPrefab(GameObject& objDroppingCoin);
private:
    float mCoinWidth;
    float mCoinHeight;
    Vector2 mCoinSpritePosition;
    SpriteDef mCoinSpriteDef;

    void addSprite(GameObject* gameObject);
    void addRigidBody(GameObject* gameObject);
    void addCollider(GameObject* gameObject);
    void setTransform(GameObject* gameObject, Transform objDroppingCoinTransform);
};