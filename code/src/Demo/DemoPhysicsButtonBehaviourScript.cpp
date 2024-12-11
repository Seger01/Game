#include "DemoPhysicsButtonBehaviourScript.h"
#include <BoxCollider.h>
#include <CircleCollider.h>
#include <EngineBravo.h>
#include <FSConverter.h>
#include <RigidBody.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <iostream>

DemoPhysicsButtonBehaviourScript::DemoPhysicsButtonBehaviourScript() {}

void DemoPhysicsButtonBehaviourScript::onStart()
{
	mButtonPressed = false;
	mBoxSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{304, 402, 16, 14}, 16, 14};

	mCircleSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{292, 439, 7, 6}, 7, 6};
}

void DemoPhysicsButtonBehaviourScript::onUpdate() {}

void DemoPhysicsButtonBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject == nullptr)
	{
		return;
	}
	if (aGameObject->getTag() == "Player")
	{
		updateButtonState();
	}
}

void DemoPhysicsButtonBehaviourScript::updateButtonState()
{
	if (!mButtonPressed)
	{
		if (mGameObject->getTag() == "ButtonBox")
		{
			std::cout << "Spawning Box" << std::endl;
			spawnBox();
		}
		else if (mGameObject->getTag() == "ButtonCircle")
		{
			std::cout << "Spawning Circle" << std::endl;
			spawnCircle();
		}
		for (Component* component : mGameObject->getComponents<Sprite>())
		{
			if (component->getTag() == "ButtonDownSprite")
			{
				component->setActive(true);
			}
			else if (component->getTag() == "ButtonUpSprite")
			{
				component->setActive(false);
			}
		}
		mButtonPressed = true;
	}
	else
	{
		if (mGameObject->getTag() == "ButtonBox")
		{
			std::cout << "Removing Box" << std::endl;
			removeBox();
		}
		else if (mGameObject->getTag() == "ButtonCircle")
		{
			std::cout << "Removing Circle" << std::endl;
			removeCircle();
		}
		for (Component* component : mGameObject->getComponents<Sprite>())
		{
			if (component->getTag() == "ButtonDownSprite")
			{
				component->setActive(false);
			}
			else if (component->getTag() == "ButtonUpSprite")
			{
				component->setActive(true);
			}
		}
		mButtonPressed = false;
	}
}

void DemoPhysicsButtonBehaviourScript::spawnBox()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();

	GameObject* box = new GameObject();
	box->setTag("Box");
	box->setName("Box");
	Transform transform;
	transform.position = Vector2(176, 432);
	box->setTransform(transform);

	Sprite* sprite = engine.getResourceManager().createSprite(mBoxSpriteDef);
	sprite->setLayer(3);
	box->addComponent(sprite);

	RigidBody* rigidBody = new RigidBody();
	rigidBody->setDensity(1.0f);
	rigidBody->setRestitution(1.0f);
	rigidBody->addForce(Vector2(-2000, -10000));
	box->addComponent(rigidBody);

	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->setWidth(sprite->getWidth() + 1);
	boxCollider->setHeight(sprite->getHeight());
	boxCollider->setTrigger(false);
	box->addComponent(boxCollider);

	scene->addGameObject(box);
}

void DemoPhysicsButtonBehaviourScript::spawnCircle()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();

	GameObject* circle = new GameObject;
	circle->setTag("Circle");
	circle->setName("Circle");
	Transform transform;
	transform.position = Vector2(176, 512);
	circle->setTransform(transform);

	Sprite* sprite = engine.getResourceManager().createSprite(mCircleSpriteDef);
	sprite->setLayer(3);
	circle->addComponent(sprite);

	RigidBody* rigidBody = new RigidBody();
	rigidBody->setDensity(1.0f);
	rigidBody->setCanRotate(true);
	rigidBody->setRestitution(1.0f);
	rigidBody->addForce(Vector2(-200, -200));
	circle->addComponent(rigidBody);

	CircleCollider* circleCollider = new CircleCollider();
	circleCollider->setRadius(sprite->getWidth() / 2);
	circleCollider->setIsTrigger(false);
	circleCollider->setTransform(Vector2(4, 4));
	circle->addComponent(circleCollider);

	scene->addGameObject(circle);
}

void DemoPhysicsButtonBehaviourScript::removeBox()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();
	if (scene->getGameObjectsWithTag("Box").size() > 0)
	{
		scene->requestGameObjectRemoval(scene->getGameObjectsWithTag("Box")[0]);
	}
}

void DemoPhysicsButtonBehaviourScript::removeCircle()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();
	if (scene->getGameObjectsWithTag("Circle").size() > 0)
	{
		scene->requestGameObjectRemoval(scene->getGameObjectsWithTag("Circle")[0]);
	}
}
