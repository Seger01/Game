#include "BulletDestroyParticleBehaviourScript.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <Global/Time.h>

void BulletDestroyParticleBehaviourScript::onStart() { mElapsedTime = 0.0; }

void BulletDestroyParticleBehaviourScript::onUpdate()
{
	mElapsedTime += Time::deltaTime;
	if (mElapsedTime >= 0.5)
	{
		EngineBravo& engine = EngineBravo::getInstance();
		SceneManager& sceneManager = engine.getSceneManager();
		sceneManager.getCurrentScene().requestGameObjectRemoval(mGameObject);
	}
}
