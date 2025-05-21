#include "DemoBulletSpawner.h"
#include "BulletBehaviourScript.h"
#include "UI/Text.h"
#include <Components/RigidBody.h>
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Global/Time.h>
#include <Scene.h>
#include <iostream>

DemoBulletSpawner::DemoBulletSpawner() : mMaxBullets(1000), mSpawnInterval(0.016f), mTimeSinceLastSpawn(0.0f) {}

void DemoBulletSpawner::onStart()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();

	mTextObject = new GameObject();
	mTextObject->setTag("SpawnedBulletsText");
	mTextObject->setTransform(Transform(Vector2(10, 10))); // Position the text at the top-left corner

	Text* textPar = new Text("Spawned Bullets: 0", "Arial", Color(0, 255, 0), Vector2(0, 0), Vector2(1, 1));
	textPar->setLayer(5);
	textPar->setTag("SpawnedBulletsText");
	textPar->setParent(*mTextObject);

	scene.addGameObject(textPar);
	scene.addGameObject(mTextObject);
}

void DemoBulletSpawner::onUpdate()
{
	mTimeSinceLastSpawn += Time::deltaTime;

	if (mBullets.size() < mMaxBullets && mTimeSinceLastSpawn >= mSpawnInterval)
	{
		EngineBravo& engine = EngineBravo::getInstance();
		Scene& scene = engine.getSceneManager().getCurrentScene();

		GameObject& playerObject = scene.getGameObjectsWithTag("Player").at(0);

		GameObject& bullet = *mBulletFactory.createBulletPrefab(playerObject);
		bullet.setTag("Bullet");
		if (bullet.hasComponent<BulletBehaviourScript>())
		{
			BulletBehaviourScript& bulletBehaviourScript = bullet.getComponents<BulletBehaviourScript>()[0];
			bullet.removeComponent(&bulletBehaviourScript);
		}

		if (bullet.hasComponent<RigidBody>())
		{
			RigidBody& rigidBody = bullet.getComponents<RigidBody>()[0];
			rigidBody.setRestitution(1.0f);
			rigidBody.addForce(Vector2(rand() % 32000 - 16000, rand() % 32000 - 16000));
		}

		if (bullet.hasComponent<CircleCollider>())
		{
			CircleCollider& boxCollider = bullet.getComponents<CircleCollider>()[0];
			boxCollider.setIsTrigger(false);
			boxCollider.setCollideCategory(2);
			boxCollider.setCollideWithCategory({1});
		}
		Transform transform;
		transform.position = Vector2(240, 240);
		bullet.setTransform(transform);
		scene.addGameObject(&bullet);

		mBullets.push_back(&bullet);
		mTimeSinceLastSpawn = 0.0f;

		if (mTextObject)
		{
			std::vector<std::reference_wrapper<GameObject>> children = mTextObject->getChildren();
			for (GameObject& child : children)
			{
				if (child.getTag() == "SpawnedBulletsText")
				{
					Text& textComponent = dynamic_cast<Text&>(child);
					textComponent.setText("Spawned Bullets: " + std::to_string(mBullets.size()));
				}
			}
		}
	}
}

void DemoBulletSpawner::onCollide(GameObject* aGameObject)
{
	if (aGameObject == nullptr)
	{
		return;
	}
}
