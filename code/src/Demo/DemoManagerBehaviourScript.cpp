#include "DemoManagerBehaviourScript.h"
#include "DemoButtonBehaviourScript.h"
#include "DemoEndOfLevelTriggerBehaviourScript.h"
#include "DemoLevel2Behaviour.h"
#include "EnemyPrefab.h"
#include "Input.h"
#include "LevelCreatorBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
#include "LevelManagerPrefab.h"
#include "MainMenuPrefab.h"
#include "PlayerPrefab.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <iostream>

SpriteDef buttonUpSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{16, 208, 16, 16}, 16, 16};
SpriteDef buttonDownSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{32, 208, 16, 16}, 16, 16};

void DemoManagerBehaviourScript::createFirstScene()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene* scene = sceneManager.createScene("DemoScene1");
	if (scene == nullptr)
	{
		exit(1);
	}

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setRenderOrder(0);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene->addGameObject(camera);

	Camera* miniMapCamera = new Camera;
	miniMapCamera->setTag("MiniMapCamera");
	miniMapCamera->setActive(true);

	miniMapCamera->setRenderOrder(1);

	miniMapCamera->setViewport(FRect{0.7, 0.7, 0.3, 0.3});

	miniMapCamera->getDebugOverlayRef().renderCameraViewport = true;
	miniMapCamera->getDebugOverlayRef().renderColliders = true;

	miniMapCamera->setBackgroundColor(Color(0, 0, 150, 100));

	miniMapCamera->setTransform(Transform(Vector2(170, 96)));
	miniMapCamera->setWidth(16 * 20);
	miniMapCamera->setHeight(9 * 20);

	scene->addGameObject(miniMapCamera);

	FSConverter fsconverter;
	std::string path = fsconverter.getResourcePath("LevelDefs/demoLevel1.json");
	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelCreatorBehaviourScript().createLevel(scene, mTileMapData);
	GameObject* defaultPlayerPrefab = PlayerPrefabFactory().createPlayerPrefab();

	// defaultPlayerPrefab->setTransform(Transform(Vector2(40, 40)));

	defaultPlayerPrefab->setTransform(Transform(Vector2(40, 40)));

	scene->addPersistentGameObject(defaultPlayerPrefab);

	GameObject* button = new GameObject;
	button->setTransform(Transform(Vector2(208, 128)));

	Sprite* buttonDownSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonDownSpriteDef);
	buttonDownSprite->setLayer(1);
	buttonDownSprite->setTag("ButtonDownSprite");
	buttonDownSprite->setActive(false);
	Sprite* buttonUpSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonUpSpriteDef);
	buttonUpSprite->setLayer(1);
	buttonUpSprite->setTag("ButtonUpSprite");
	buttonDownSprite->setActive(true);

	button->addComponent(buttonDownSprite);
	button->addComponent(buttonUpSprite);

	button->addComponent<DemoButtonBehaviourScript>();
	button->addComponent<RigidBody>();

	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->setWidth(buttonUpSprite->getWidth());
	boxCollider->setHeight(buttonUpSprite->getHeight());
	boxCollider->setTrigger(true);

	button->addComponent(boxCollider);

	scene->addGameObject(button);

	GameObject* endOfLevelTrigger = new GameObject;
	endOfLevelTrigger->setTransform(Transform(Vector2(260, 64)));
	endOfLevelTrigger->setTag("EndOfLevelTrigger");
	endOfLevelTrigger->addComponent<DemoEndOfLevelTriggerBehaviourScript>();

	endOfLevelTrigger->addComponent<RigidBody>();
	BoxCollider* endOfLevelTriggerCollider = new BoxCollider();
	endOfLevelTriggerCollider->setWidth(16);
	endOfLevelTriggerCollider->setHeight(16);
	endOfLevelTriggerCollider->setTrigger(true);
	endOfLevelTrigger->addComponent(endOfLevelTriggerCollider);

	scene->addGameObject(endOfLevelTrigger);

	sceneManager.requestSceneChange("DemoScene1");

	mPlayerPositionSet = false;
}

void DemoManagerBehaviourScript::createSecondScene()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene* scene = sceneManager.createScene("DemoScene2");
	if (scene == nullptr)
	{
		exit(1);
	}

	// set starting pos for player in this scene
	// GameObject* playerObject = sceneManager.getCurrentScene()->getGameObjectsWithTag("Player").at(0);
	// playerObject->setTransform(Transform(Vector2(40, 40)));
	GameObject* playerObject =
		EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("Player").at(0);
	playerObject->setTransform(Transform(Vector2(40, 40)));
	//  playerObject->setTransform(Transform(Vector2(40, 40)));

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene->addGameObject(camera);

	FSConverter fsconverter;
	std::string path = fsconverter.getResourcePath("LevelDefs/demoLevel2.json");
	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelCreatorBehaviourScript().createLevel(scene, mTileMapData);
	// GameObject* defaultPlayerPrefab = PlayerPrefabFactory().createPlayerPrefab();
	//
	// defaultPlayerPrefab->setTransform(Transform(Vector2(40, 40)));
	//
	// scene->addPersistentGameObject(defaultPlayerPrefab);

	// GameObject* defaultPlayerPrefab = PlayerPrefabFactory().createPlayerPrefab();
	//
	// defaultPlayerPrefab->setTransform(Transform(Vector2(40, 40)));
	//
	// scene->addPersistentGameObject(defaultPlayerPrefab);

	// GameObject* button = new GameObject;
	// button->setTransform(Transform(Vector2(208, 128)));
	//
	// Sprite* buttonDownSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonDownSpriteDef);
	// buttonDownSprite->setLayer(1);
	// buttonDownSprite->setTag("ButtonDownSprite");
	// buttonDownSprite->setActive(false);
	// Sprite* buttonUpSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonUpSpriteDef);
	// buttonUpSprite->setLayer(1);
	// buttonUpSprite->setTag("ButtonUpSprite");
	// buttonDownSprite->setActive(true);
	//
	// button->addComponent(buttonDownSprite);
	// button->addComponent(buttonUpSprite);
	//
	// button->addComponent<DemoButtonBehaviourScript>();
	// button->addComponent<RigidBody>();
	//
	// BoxCollider* boxCollider = new BoxCollider();
	// boxCollider->setWidth(buttonUpSprite->getWidth());
	// boxCollider->setHeight(buttonUpSprite->getHeight());
	// boxCollider->setTrigger(true);
	//
	// button->addComponent(boxCollider);
	//
	// scene->addGameObject(button);

	GameObject* endOfLevelTrigger = new GameObject;
	endOfLevelTrigger->setTransform(Transform(Vector2(125, 65)));
	endOfLevelTrigger->setTag("EndOfLevelTrigger");
	endOfLevelTrigger->addComponent<DemoEndOfLevelTriggerBehaviourScript>();

	endOfLevelTrigger->addComponent<RigidBody>();
	BoxCollider* endOfLevelTriggerCollider = new BoxCollider();
	endOfLevelTriggerCollider->setWidth(16);
	endOfLevelTriggerCollider->setHeight(16);
	endOfLevelTriggerCollider->setTrigger(true);
	endOfLevelTrigger->addComponent(endOfLevelTriggerCollider);

	GameObject* enemyMoving = EnemyPrefab().createEnemyPrefab();
	GameObject* enemyStatic = EnemyPrefab().createEnemyPrefab();
	GameObject* enemyWithCollider = EnemyPrefab().createEnemyPrefab();

	enemyMoving->setTransform(Transform(Vector2(112, 112)));
	enemyMoving->setTag("EnemyMoving");

	enemyStatic->setTransform(Transform(Vector2(40, 84)));
	enemyStatic->setTag("EnemyStatic");

	enemyWithCollider->setTransform(Transform(Vector2(320, 112)));
	enemyWithCollider->setTag("EnemyWithCollider");

	if (enemyStatic->hasComponent<RigidBody>())
	{
		enemyStatic->getComponents<RigidBody>().at(0)->setCanRotate(true);
	}
	else
	{
		std::cout << "Enemystatic does not have a RigidBody component" << std::endl;
	}

	if (enemyWithCollider->hasComponent<RigidBody>())
	{
		enemyWithCollider->getComponents<RigidBody>().at(0)->setCanRotate(true);
	}
	else
	{
		std::cout << "Enemystatic does not have a RigidBody component" << std::endl;
	}

	scene->addGameObject(enemyMoving);
	scene->addGameObject(enemyStatic);
	scene->addGameObject(enemyWithCollider);

	GameObject* level2 = new GameObject;
	level2->addComponent<DemoLevel2Behaviour>();

	scene->addGameObject(level2);

	sceneManager.requestSceneChange("DemoScene2");

	mPlayerPositionSet = true;

	saveGame();
}

void DemoManagerBehaviourScript::nextScene()
{
	mCurrentScene++;
	switch (mCurrentScene)
	{
	case 1:
		createSecondScene();
		break;
	default:
		break;
	}
}

void DemoManagerBehaviourScript::onStart()
{
	std::cout << "DemoInitBehaviourScript::onStart()" << std::endl;

	mCurrentScene = 0;
	createFirstScene();
}

void DemoManagerBehaviourScript::onUpdate()
{
	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_Space))
	{
		GameObject* playerObject =
			EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("Player").at(0);
		std::cout << "Setting player transform" << std::endl;
		playerObject->setTransform(Transform(Vector2(40, 40)));
	}

	if (!mPlayerPositionSet)
	{
		EngineBravo& engine = EngineBravo::getInstance();
		SceneManager& sceneManager = engine.getSceneManager();
		Scene* currentScene = sceneManager.getCurrentScene();

		if (currentScene != nullptr)
		{
			std::vector<GameObject*> persistentObjects = currentScene->getPersistentGameObjects();
			auto playerIt = std::find_if(persistentObjects.begin(), persistentObjects.end(),
										 [](GameObject* obj) { return obj->getTag() == "Player"; });

			if (playerIt != persistentObjects.end())
			{
				LevelCreatorBehaviourScript().setPlayerStartPosition(currentScene, mTileMapData);
				mPlayerPositionSet = true; // Set the flag to true
			}
		}
	}
}

void DemoManagerBehaviourScript::saveGame()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* currentScene = sceneManager.getCurrentScene();

	Transform playerPos;
	if (currentScene != nullptr)
	{
		std::vector<GameObject*> persistentObjects = currentScene->getPersistentGameObjects();
		auto playerIt = std::find_if(persistentObjects.begin(), persistentObjects.end(),
									 [](GameObject* obj) { return obj->getTag() == "Player"; });

		if (playerIt != persistentObjects.end())
		{
			playerPos = (*playerIt)->getTransform().position;
		}
	}

	SaveGame sg{"saves/newSave.json"};

	sg.addFloatField("PlayerX", playerPos.position.x);
	sg.addFloatField("PlayerY", playerPos.position.y);
	sg.addFloatField("PlayerRotation", playerPos.rotation);
	sg.addFloatField("PlayerScaleX", playerPos.scale.x);
	sg.addFloatField("PlayerScaleY", playerPos.scale.y);

	std::vector<GameObject*> enemies = currentScene->getGameObjectsWithTag("Enemy");
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		Transform enemyPos = enemies[i]->getTransform().position;
		sg.addFloatField("Enemy" + std::to_string(i) + "X", enemyPos.position.x);
		sg.addFloatField("Enemy" + std::to_string(i) + "Y", enemyPos.position.y);
		sg.addFloatField("Enemy" + std::to_string(i) + "Rotation", enemyPos.rotation);
		sg.addFloatField("Enemy" + std::to_string(i) + "ScaleX", enemyPos.scale.x);
		sg.addFloatField("Enemy" + std::to_string(i) + "ScaleY", enemyPos.scale.y);
	}

	sg.store();
}
