#include "BSCoinPrefab.h"

BSCoinPrefab::BSCoinPrefab() {
    mCoinWidth = 6.0f;
    mCoinHeight = 6.0f;
    mCoinSpritePosition = {0.0f, 0.0f}; // Adjust the sprite position as needed

    FSConverter fsConverter;
    std::string coinSpritePath = fsConverter.getResourcePath("Coins/Money.png");
    mCoinSpriteDef = {
        coinSpritePath,
        Rect(),
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
    boxCollider->setWidth(6);
    boxCollider->setHeight(6);
    //boxCollider->setTrigger(true);
    gameObject->addComponent(boxCollider);
}

void BSCoinPrefab::setTransform(GameObject* gameObject, Transform objDroppingCoinTransform) {
    Transform objectTransform;
    objectTransform.position.x = objDroppingCoinTransform.position.x;
    objectTransform.position.y = objDroppingCoinTransform.position.y;
    gameObject->setTransform(objectTransform);
}
