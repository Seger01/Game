#include "ECCoinPrefab.h"

ECCoinPrefab::ECCoinPrefab() {
    mCoinWidth = 16;
    mCoinHeight = 16;
    mCoinSpritePosition = {0, 0}; // Adjust the sprite position as needed

    FSConverter fsConverter;
    std::string coinSpritePath = fsConverter.getResourcePath("Coins/ec_coin_circle.png");
    mCoinSpriteDef = {
        coinSpritePath,
        Rect{mCoinSpritePosition.x, mCoinSpritePosition.y, mCoinWidth, mCoinHeight},
        mCoinWidth, mCoinHeight
    };
}

GameObject* ECCoinPrefab::createECCoinPrefab(GameObject& objDroppingCoin) {
    GameObject* coinPrefab = new GameObject;
    coinPrefab->setTag("ECCoin");
    addSprite(coinPrefab);
    return coinPrefab;
}

void ECCoinPrefab::addSprite(GameObject* gameObject) {
    Sprite* coinSprite = EngineBravo::getInstance().getResourceManager().createSprite(mCoinSpriteDef);
    coinSprite->setLayer(3);
    gameObject->addComponent(coinSprite);
}

void ECCoinPrefab::addRigidBody(GameObject* gameObject) {
    RigidBody* rigidBody = new RigidBody();
    rigidBody->setCanRotate(true);
    rigidBody->setHasGravity(false);
    rigidBody->setIsMoveableByForce(true);
    rigidBody->setDensity(1.0f);
    rigidBody->setFriction(0.0f);
    rigidBody->setRestitution(0.0f);
    rigidBody->setGravityScale(0.0f);
    rigidBody->setMass(0.0f);
    rigidBody->setLinearDamping(0.0f);
    rigidBody->setAngularDamping(0.0f);
    gameObject->addComponent(rigidBody);
}

void ECCoinPrefab::addCollider(GameObject* gameObject) {
   // CircleCollider* circleCollider = new CircleCollider();
    //circleCollider->setIsTrigger(true);
   // circleCollider->setRadius(8.0f);
    BoxCollider* boxCollider = new BoxCollider();
    boxCollider->setWidth(16);
    boxCollider->setHeight(16);
   // boxCollider->setTrigger(true);
    gameObject->addComponent(boxCollider);
}

void ECCoinPrefab::setTransform(GameObject* gameObject, Transform objDroppingCoinTransform) {
    Transform objectTransform;
    objectTransform.position.x = objDroppingCoinTransform.position.x;
    objectTransform.position.y = objDroppingCoinTransform.position.y;
    gameObject->setTransform(objectTransform);
}

