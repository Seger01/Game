#include "EnemyPrefab.h"
#include "EnemyBehaviourScript.h"
#include "EnemyNetworkBehaviourScript.h"
#include "EnemyNetworkBehaviourTransform.h"
#include <Animation.h>
#include <Components/Sprite.h>
#include <Engine/EngineBravo.h>
#include <GameObject.h>
#include <Network/NetworkObject.h>
#include <Network/NetworkTransform.h>
#include <SpriteDef.h>
#include <SpriteDefUtil.h>
#include <Transform.h>

REGISTER_NETWORK_PREFAB(EnemyPrefab);

const int enemySpriteWidth = 20;  // Width of each sprite
const int enemySpriteHeight = 27; // Height of each sprite

const Point enemyIdlePosition = {53, 389};
SpriteDef firstFrameEnemyIdle = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png",
								 Rect{enemyIdlePosition.x, enemyIdlePosition.y, enemySpriteWidth, enemySpriteHeight},
								 16, 16};

const Point enemyWalkingPosition = {16, 388};
SpriteDef firstFrameEnemyWalking = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png",
									Rect{enemyWalkingPosition.x, enemyWalkingPosition.y, 32, 28}, 32, 28};

EnemyPrefab::EnemyPrefab() {}

GameObject* EnemyPrefab::createEnemyPrefab()
{
	GameObject* enemy = new GameObject;
	if (EngineBravo::getInstance().getNetworkManager().isNetworked())
	{
		enemy->addComponent<NetworkObject>();
		enemy->addComponent<EnemyNetworkBehaviourTransform>();
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
	enemy->setTag("enemy");
	return enemy;
}

int EnemyPrefab::getPrefabID() const { return GetTypeId<EnemyPrefab>(); }

void EnemyPrefab::setTransform(GameObject* gameObject)
{
	Transform transform;
	transform.position = Vector2(128, 112);
	gameObject->setTransform(transform);
}

void EnemyPrefab::addSprite(GameObject* gameObject)
{
	EngineBravo& engine = EngineBravo::getInstance();
	Sprite* sprite = engine.getResourceManager().createSprite(firstFrameEnemyIdle);
	sprite->setLayer(3);
	sprite->setTag("idleSprite");
	gameObject->addComponent(sprite);
}

void EnemyPrefab::addRigidBody(GameObject* gameObject)
{
	RigidBody* rigidBody = new RigidBody();
	rigidBody->setTransform(gameObject->getTransform());
	rigidBody->setDensity(1.0f);
	gameObject->addComponent(rigidBody);
}

void EnemyPrefab::addCollider(GameObject* gameObject)
{
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->setWidth(firstFrameEnemyIdle.width);
	boxCollider->setHeight(firstFrameEnemyIdle.height);
	boxCollider->setTransform(gameObject->getTransform());
	gameObject->addComponent(boxCollider);
}

void EnemyPrefab::addAnimations(GameObject* gameObject)
{
	EngineBravo& engine = EngineBravo::getInstance();

	Animation* enemyWalkingAnimation = nullptr;

	{
		std::vector<SpriteDef> enemyWalkingAnimationFrames =
			SpriteDefUtil::extrapolateSpriteDef(firstFrameEnemyWalking, 8);

		enemyWalkingAnimation = engine.getResourceManager().loadAnimation(enemyWalkingAnimationFrames, 400, true);
	}

	enemyWalkingAnimation->setTag("enemyWalking");

	gameObject->addComponent(enemyWalkingAnimation);

	for (auto animation : gameObject->getComponents<Animation>())
	{
		animation.get().setActive(false);
		animation.get().setLayer(2);
	}
	enemyWalkingAnimation->setActive(false);
}
