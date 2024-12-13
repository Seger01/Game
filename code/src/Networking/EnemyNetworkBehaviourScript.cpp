#include "EnemyNetworkBehaviourScript.h"
#include "BSCoinPrefab.h"
#include "BulletBehaviourScript.h"
#include "ECCoinPrefab.h"
#include <Animation.h>

EnemyNetworkBehaviourScript::EnemyNetworkBehaviourScript(float aHealth)
	: INetworkBehaviour("EnemyNetworkBehaviour"), mHealth(aHealth)
{
}

void EnemyNetworkBehaviourScript::onStart() { mIsDead = false; }

void EnemyNetworkBehaviourScript::onUpdate() {}

void EnemyNetworkBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (mIsDead)
	{
		return;
	}

	if (aGameObject->getTag() == "Bullet")
	{
		BulletBehaviourScript& bullet = aGameObject->getComponents<BulletBehaviourScript>().at(0);
		// takeDamage(bullet->getDamage());
	}
}

void EnemyNetworkBehaviourScript::toggleAnimaionEnabled() {}

void EnemyNetworkBehaviourScript::setAnimationActive(std::string aAnimationTag, bool aState) {}

void EnemyNetworkBehaviourScript::deactivateAllAnimations()
{
	for (auto animation : mGameObject->getComponents<Animation>())
	{
		animation.get().setActive(false);
	}
}

void EnemyNetworkBehaviourScript::setFlipX(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (auto animation : mGameObject->getComponents<Animation>())
		{
			animation.get().setFlipX(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (auto sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.get().setFlipX(aState);
		}
	}
}

void EnemyNetworkBehaviourScript::setFlipY(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (auto animation : mGameObject->getComponents<Animation>())
		{
			animation.get().setFlipY(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (auto sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.get().setFlipY(aState);
		}
	}
}

void EnemyNetworkBehaviourScript::takeDamage(float aDamage)
{
	if (mHealth <= 0)
	{
		onDeath();
	}
	else
	{
		mHealth -= aDamage;
	}
}

void EnemyNetworkBehaviourScript::onDeath()
{
	if (mIsDead)
	{
		return;
	}
	mIsDead = true;

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	if (mGameObject != nullptr)
	{
		//  std::cout << "Creating Coins" << std::endl;
		// BSCoinPrefab coinPrefab;
		// GameObject* coin = coinPrefab.createBSCoinPrefab(*mGameObject);
		// sceneManager.getCurrentScene()->addGameObject(coin);

		//  ECCoinPrefab coinPrefab2;
		// GameObject* coin2 = coinPrefab2.createECCoinPrefab(*mGameObject);
		//  sceneManager.getCurrentScene()->addGameObject(coin2);

		std::cout << "Removing GameObject: " << mGameObject->getTag() << std::endl;
		sceneManager.getCurrentScene().requestGameObjectRemoval(mGameObject);
	}
	else
	{
		std::cerr << "Error: mGameObject is already null!" << std::endl;
	}
}
