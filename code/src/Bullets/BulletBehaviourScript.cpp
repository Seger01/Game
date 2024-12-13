#include "BulletBehaviourScript.h"

BulletBehaviourScript::BulletBehaviourScript(float damage) : mDamage(damage) { mIsMarkedForRemoval = false; }

void BulletBehaviourScript::onStart() {}

void BulletBehaviourScript::onUpdate() {}

void BulletBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (mIsMarkedForRemoval)
	{
		return;
	}

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	if (aGameObject->getTag() != "Player")
	{
		mIsMarkedForRemoval = true;
		mGameObject->getComponents<RigidBody>().at(0).get().setActive(false);
		sceneManager.getCurrentScene()->requestGameObjectRemoval(mGameObject);
	}
}
