#include "EnemyPrefab.h"
#include "EnemyBehaviourScript.h"
#include "EnemyNetworkBehaviourScript.h"
#include <Animation.h>
#include <EngineBravo.h>
#include <GameObject.h>
#include <NetworkObject.h>
#include <NetworkTransform.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <SpriteDefUtil.h>
#include <Transform.h>

const int enemySpriteWidth = 20;  // Width of each sprite
const int enemySpriteHeight = 27; // Height of each sprite

const Point enemyIdlePosition = {53, 389};
SpriteDef firstFrameEnemyIdle = {
    "Dungeontileset/0x72_DungeonTilesetII_v1.7.png",
    Rect{enemyIdlePosition.x, enemyIdlePosition.y, enemySpriteWidth, enemySpriteHeight},
    enemySpriteWidth, enemySpriteHeight};

const Point enemyWalkingPosition = {22, 389};
SpriteDef firstFrameEnemyWalking = {
    "Dungeontileset/0x72_DungeonTilesetII_v1.7.png",
    Rect{enemyWalkingPosition.x, enemyWalkingPosition.y, enemySpriteWidth, enemySpriteHeight},
    enemySpriteWidth, enemySpriteHeight};

EnemyPrefab::EnemyPrefab() {}

GameObject* EnemyPrefab::createEnemyPrefab() {
    GameObject* enemy = new GameObject;
    //setTransform(enemy);
	if (EngineBravo::getInstance().getNetworkManager().isNetworked())
	{
		enemy->addComponent<NetworkObject>();
		enemy->addComponent<NetworkTransform>(true, true, false, false, false);
		enemy->addComponent<EnemyNetworkBehaviourScript>(100.0f);
	}
	else
	{
		enemy->addComponent<EnemyBehaviourScript>(100.0f);
	}
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
    EngineBravo& engine = EngineBravo::getInstance();
    Sprite* sprite = engine.getResourceManager().createSprite(firstFrameEnemyIdle);
    sprite->setLayer(3);
    gameObject->addComponent(sprite);
}

void EnemyPrefab::addRigidBody(GameObject* gameObject) {
    RigidBody* rigidBody = new RigidBody();
    rigidBody->setTransform(gameObject->getTransform());
    rigidBody->setDensity(1.0f);
    gameObject->addComponent(rigidBody);
}

void EnemyPrefab::addCollider(GameObject* gameObject) {
    BoxCollider* boxCollider = new BoxCollider();
    boxCollider->setWidth(firstFrameEnemyIdle.width);
    boxCollider->setHeight(firstFrameEnemyIdle.height);
    boxCollider->setTransform(gameObject->getTransform());
    gameObject->addComponent(boxCollider);
}

void EnemyPrefab::addAnimations(GameObject* gameObject) {
    EngineBravo& engine = EngineBravo::getInstance();

    Animation* enemyIdleAnimation = nullptr;
    Animation* enemyWalkingAnimation = nullptr;

    {
        std::vector<SpriteDef> enemyIdleAnimationFrames =
            SpriteDefUtil::extrapolateSpriteDef(firstFrameEnemyIdle, 4);

        std::vector<SpriteDef> enemyAnimationIdle = {
            enemyIdleAnimationFrames[0], enemyIdleAnimationFrames[1], enemyIdleAnimationFrames[2],
            enemyIdleAnimationFrames[3]};

        enemyIdleAnimation =
            engine.getResourceManager().loadAnimation(enemyAnimationIdle, 100, true);
    }

    {
        std::vector<SpriteDef> enemyWalkingAnimationFrames =
            SpriteDefUtil::extrapolateSpriteDef(firstFrameEnemyWalking, 4);

        std::vector<SpriteDef> enemyAnimationWalking = {
            enemyWalkingAnimationFrames[0], enemyWalkingAnimationFrames[1], enemyWalkingAnimationFrames[2],
            enemyWalkingAnimationFrames[3]};

        enemyWalkingAnimation =
            engine.getResourceManager().loadAnimation(enemyAnimationWalking, 100, true);
    }

    enemyIdleAnimation->setTag("enemyIdle");
    enemyWalkingAnimation->setTag("enemyWalking");

    gameObject->addComponent(enemyIdleAnimation);
    gameObject->addComponent(enemyWalkingAnimation);

    for (auto animation : gameObject->getComponents<Animation>()) {
        animation->setActive(false);
        animation->setLayer(2);
    }

    enemyIdleAnimation->setActive(true);
}