#include "BSCoinPrefab.h"

BSCoinPrefab::BSCoinPrefab() {
    mCoinWidth = 16;
    mCoinHeight = 16;
    mCoinSpritePosition = {0, 0}; // Adjust the sprite position as needed

    FSConverter fsConverter;
    std::string coinSpritePath = fsConverter.getResourcePath("Coins/bs_coin_circle.png");
    mCoinSpriteDef = {
        coinSpritePath,
        Rect{mCoinSpritePosition.x, mCoinSpritePosition.y, mCoinWidth, mCoinHeight},
        mCoinWidth, mCoinHeight
    };
}

GameObject* BSCoinPrefab::createBSCoinPrefab(GameObject& objDroppingCoin) {
    GameObject* coinPrefab = new GameObject;
    coinPrefab->setTag("BSCoin");
    coinPrefab->addComponent<BSCoinBehaviourScript>();
    addSprite(coinPrefab);
    addRigidBody(coinPrefab);
    addCollider(coinPrefab);
    setTransform(coinPrefab, objDroppingCoin.getTransform());
    return coinPrefab;
}

void BSCoinPrefab::addSprite(GameObject* gameObject) {
    Sprite* coinSprite = EngineBravo::getInstance().getResourceManager().createSprite(mCoinSpriteDef);
    coinSprite->setLayer(3);
    gameObject->addComponent(coinSprite);
}

void BSCoinPrefab::addRigidBody(GameObject* gameObject) {
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

void BSCoinPrefab::addCollider(GameObject* gameObject) {
    //CircleCollider* circleCollider = new CircleCollider();
    //circleCollider->setIsTrigger(true);
    //circleCollider->setRadius(8.0f);
    //gameObject->addComponent(circleCollider);

    BoxCollider* boxCollider = new BoxCollider();
    boxCollider->setWidth(16);
    boxCollider->setHeight(16);
    //boxCollider->setTrigger(true);
    gameObject->addComponent(boxCollider);
}

void BSCoinPrefab::setTransform(GameObject* gameObject, Transform objDroppingCoinTransform) {
    Transform objectTransform;
    objectTransform.position.x = objDroppingCoinTransform.position.x;
    objectTransform.position.y = objDroppingCoinTransform.position.y;
    gameObject->setTransform(objectTransform);
}
