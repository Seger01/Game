#include "EnemyPrefab.h"
#include <Sprite.h>
#include <SpriteDef.h>
#include <EngineBravo.h>
#include <RigidBody.h>
#include <BoxCollider.h>
#include <Animation.h>

SpriteDef enemySpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{182, 389, 20, 27}, 20, 27};

EnemyPrefab::EnemyPrefab() {}

GameObject* EnemyPrefab::createEnemyPrefab() {
    GameObject* enemy = new GameObject;
    setTransform(enemy);
    addSprite(enemy);
    addRigidBody(enemy);
    addCollider(enemy);
    addAnimations(enemy);
    return enemy;
}

void EnemyPrefab::setTransform(GameObject* gameObject) {
    Transform transform;
    transform.position = Vector2(128, 112);
    gameObject->setTransform(transform);
}

void EnemyPrefab::addSprite(GameObject* gameObject) {
    Sprite* sprite = EngineBravo::getInstance().getResourceManager().createSprite(enemySpriteDef);
    sprite->setLayer(1);
    gameObject->addComponent(sprite);
}

void EnemyPrefab::addRigidBody(GameObject* gameObject) {
    RigidBody* rigidBody = new RigidBody();
    rigidBody->setTransform(gameObject->getTransform());
   // rigidBody->setHasGravity(true);
    rigidBody->setDensity(1.0f);
   // rigidBody->setFriction(0.3f);
   // rigidBody->setRestitution(0.2f);
    rigidBody->setMass(1.0f);
    //rigidBody->setGravityScale(10.0f);
    rigidBody->setCanRotate(true);
    gameObject->addComponent(rigidBody);
}

void EnemyPrefab::addCollider(GameObject* gameObject) {
    BoxCollider* boxCollider = new BoxCollider();
    boxCollider->setWidth(enemySpriteDef.width);
    boxCollider->setHeight(enemySpriteDef.height);
    boxCollider->setTransform(gameObject->getTransform());
    gameObject->addComponent(boxCollider);
}

void EnemyPrefab::addAnimations(GameObject* gameObject) {
    // Animation* animation = new Animation();
    // animation->setTag("idle");
    // animation->setFrameTime(0.1f);
    // animation->setLoop(true);
    // animation->addFrame(Rect{0, 0, 16, 16});
    // animation->addFrame(Rect{16, 0, 16, 16});
    // animation->addFrame(Rect{32, 0, 16, 16});
    // animation->addFrame(Rect{48, 0, 16, 16});
    // gameObject->addComponent(animation);
}
