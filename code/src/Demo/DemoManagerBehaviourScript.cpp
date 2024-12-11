#include "DemoManagerBehaviourScript.h"
#include "DemoButtonBehaviourScript.h"
#include "DemoButtonPrefab.h"
#include "DemoEndOfLevelTriggerBehaviourScript.h"
#include "DemoLevel2Behaviour.h"
#include "DemoMusicButtonBehaviourScript.h"
#include "DemoSFXButtonBehaviourScript.h"
#include "EnemyPrefab.h"
#include "Input.h"
#include "LevelCreatorBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
#include "LevelManagerPrefab.h"
#include "MainMenuPrefab.h"
#include "Pathfinding.h"
#include "PlayerPrefab.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <MapToGraph.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Text.h>
#include <iostream>
#include "EnemyBehaviourScript.h"
#include "DemoPhysicsButtonBehaviourScript.h"
#include "DemoParticlesButtonBehaviourScript.h"
#include "DemoBulletSpawner.h"

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

	camera->setBackgroundColor(Color(0, 0, 0));

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

	GameObject* button = DemoButtonPrefab().createButtonPrefab();
	button->setTransform(Transform(Vector2(208, 128)));

	button->addComponent<DemoButtonBehaviourScript>();

	scene->addGameObject(button);

	GameObject* endOfLevelTrigger = new GameObject;
	endOfLevelTrigger->setTransform(Transform(Vector2(276, 64)));
	endOfLevelTrigger->setTag("EndOfLevelTriggerDemo");
	endOfLevelTrigger->addComponent<DemoEndOfLevelTriggerBehaviourScript>();

	endOfLevelTrigger->addComponent<RigidBody>();
	BoxCollider* endOfLevelTriggerCollider = new BoxCollider();
	endOfLevelTriggerCollider->setWidth(16);
	endOfLevelTriggerCollider->setHeight(16);
	endOfLevelTriggerCollider->setTrigger(true);
	endOfLevelTrigger->addComponent(endOfLevelTriggerCollider);

	scene->addGameObject(endOfLevelTrigger);


	GameObject* endOfLevelTriggerStressTest = new GameObject;
	endOfLevelTriggerStressTest->setTransform(Transform(Vector2(208, 176)));
	endOfLevelTriggerStressTest->setTag("EndOfLevelTriggerStressTest");
	endOfLevelTriggerStressTest->addComponent<DemoEndOfLevelTriggerBehaviourScript>();

	endOfLevelTriggerStressTest->addComponent<RigidBody>();
	BoxCollider* endOfLevelTriggerColliderStressTest = new BoxCollider();
	endOfLevelTriggerColliderStressTest->setWidth(16);
	endOfLevelTriggerColliderStressTest->setHeight(16);
	endOfLevelTriggerColliderStressTest->setTrigger(true);
	endOfLevelTriggerStressTest->addComponent(endOfLevelTriggerColliderStressTest);

	scene->addGameObject(endOfLevelTriggerStressTest);

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
	if (playerObject == nullptr)
	{
		std::cout << "Player not found" << std::endl;
		return;
	}
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

	MapToGraph mapToGraph(mTileMapData);
	mapToGraph.convertToGraph();
	std::unordered_map<int, std::vector<int>> graph = mapToGraph.getAdjacencyList();

	int mapWidth = 75;
	int mapHeight = 75;

	// Add button for starting and stopping music
	GameObject* buttonMusic = DemoButtonPrefab().createButtonPrefab();
	buttonMusic->setTag("ButtonStartStopMusic");
	buttonMusic->setTransform(Transform(Vector2(540, 174)));
	buttonMusic->addComponent<DemoMusicButtonBehaviourScript>();

	Text* text = new Text("Play/Stop", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.4, 0.4));
	text->setLayer(5);
	text->setTag("ButtonStartStopMusicText");
	text->setParent(buttonMusic);

	scene->addGameObject(text);
	scene->addGameObject(buttonMusic);

	// Add button for resetting music
	GameObject* buttonResetMusic = DemoButtonPrefab().createButtonPrefab();
	buttonResetMusic->setTransform(Transform(Vector2(620, 174)));
	buttonResetMusic->addComponent<DemoMusicButtonBehaviourScript>();
	buttonResetMusic->setTag("ButtonResetMusic");

	Text* textReset = new Text("Reset", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.4, 0.4));
	textReset->setLayer(5);
	textReset->setTag("ButtonResetMusicText");
	textReset->setParent(buttonResetMusic);

	scene->addGameObject(textReset);
	scene->addGameObject(buttonResetMusic);

	// Add button for SFX
	GameObject* buttonSFX = DemoButtonPrefab().createButtonPrefab();
	buttonSFX->setTag("ButtonSFX");
	buttonSFX->setTransform(Transform(Vector2(540, 56)));
	buttonSFX->addComponent<DemoSFXButtonBehaviourScript>();

	Text* textSFX = new Text("SFX", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.4, 0.4));
	textSFX->setLayer(5);
	textSFX->setTag("ButtonSFXText");
	textSFX->setParent(buttonSFX);

	scene->addGameObject(textSFX);
	scene->addGameObject(buttonSFX);

	//Add buttons for physics objects
	GameObject* button1 = DemoButtonPrefab().createButtonPrefab();
    button1->setTransform(Transform(Vector2(288, 432)));
    button1->setTag("ButtonBox");
	button1->addComponent<DemoPhysicsButtonBehaviourScript>();

    Text* text1 = new Text("Box object", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.3, 0.3));
    text1->setLayer(5);
    text1->setTag("ButtonBoxText");
    text1->setParent(button1);

    scene->addGameObject(text1);
    scene->addGameObject(button1);

    GameObject* button2 = DemoButtonPrefab().createButtonPrefab();
    button2->setTransform(Transform(Vector2(288, 512)));
    button2->setTag("ButtonCircle");
	button2->addComponent<DemoPhysicsButtonBehaviourScript>();

    Text* text2 = new Text("Circle object", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.3, 0.3));
    text2->setLayer(5);
    text2->setTag("Button2Text");
    text2->setParent(button2);

    scene->addGameObject(text2);
    scene->addGameObject(button2);

    GameObject* button3 = DemoButtonPrefab().createButtonPrefab();
    button3->setTransform(Transform(Vector2(288, 608)));
    button3->setTag("ButtonFilter");
	button3->addComponent<DemoPhysicsButtonBehaviourScript>();

    Text* text3 = new Text("Filters", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.3, 0.3));
    text3->setLayer(5);
    text3->setTag("Button3Text");
    text3->setParent(button3);

    scene->addGameObject(text3);
    scene->addGameObject(button3);


	// Add button for particle effects
	GameObject* buttonPar = DemoButtonPrefab().createButtonPrefab();
	buttonPar->setTag("ButtonPar");
	buttonPar->setTransform(Transform(Vector2(336, 816)));
	buttonPar->addComponent<DemoParticlesButtonBehaviourScript>();

	Text* textPar = new Text("Fireworks", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.2, 0.2));
	textPar->setLayer(5);
	textPar->setTag("ButtonParText");
	textPar->setParent(buttonPar);

	scene->addGameObject(textPar);
	scene->addGameObject(buttonPar);

	//Add button to toggle gravity
	GameObject* buttonGravity = DemoButtonPrefab().createButtonPrefab();
	buttonGravity->setTag("ButtonGravity");
	buttonGravity->setTransform(Transform(Vector2(288, 368)));
	buttonGravity->addComponent<DemoPhysicsButtonBehaviourScript>();

	Text* textGravity = new Text("Toggle Gravity", "Arial", Color(255, 255, 255), Vector2(0, 17), Vector2(0.3, 0.3));
	textGravity->setLayer(5);
	textGravity->setTag("ButtonGravityText");
	textGravity->setParent(buttonGravity);

	scene->addGameObject(textGravity);
	scene->addGameObject(buttonGravity);

	// Add enemies
	GameObject* enemyMoving = EnemyPrefab().createEnemyPrefab();
	GameObject* enemyStatic = EnemyPrefab().createEnemyPrefab();
	GameObject* enemyWithCollider = EnemyPrefab().createEnemyPrefab();
	GameObject* enemyWithPathfinding = EnemyPrefab().createEnemyPrefab();

	enemyMoving->setTransform(Transform(Vector2(100, 112)));
	enemyMoving->setTag("EnemyMoving");
	if (enemyMoving->hasComponent<RigidBody>())
		enemyMoving->removeComponent(enemyMoving->getComponents<RigidBody>()[0]);
	if (enemyMoving->hasComponent<BoxCollider>())
		enemyMoving->removeComponent(enemyMoving->getComponents<BoxCollider>()[0]);

	enemyStatic->setTransform(Transform(Vector2(40, 84)));
	enemyStatic->setTag("EnemyStatic");
	if (enemyStatic->hasComponent<RigidBody>())
		enemyStatic->removeComponent(enemyStatic->getComponents<RigidBody>()[0]);
	if (enemyStatic->hasComponent<BoxCollider>())
		enemyStatic->removeComponent(enemyStatic->getComponents<BoxCollider>()[0]);

	enemyWithCollider->setTransform(Transform(Vector2(320, 112)));
	enemyWithCollider->setTag("EnemyWithCollider");

	enemyWithPathfinding->setTransform(Transform(Vector2(560, 560)));
	enemyWithPathfinding->setTag("EnemyWithPathfinding");
	std::unique_ptr<Pathfinding> pathfinding = std::make_unique<Pathfinding>(graph, mapWidth, mapHeight);

	if (enemyWithPathfinding->hasComponent<EnemyBehaviourScript>())
	{
		enemyWithPathfinding->getComponents<EnemyBehaviourScript>()[0]->setPathfinding(std::move(pathfinding));
		enemyWithPathfinding->getComponents<EnemyBehaviourScript>()[0]->setMapWidth(mapWidth);
		enemyWithPathfinding->getComponents<EnemyBehaviourScript>()[0]->setMapHeight(mapHeight);
	}
	
	if (enemyWithPathfinding->hasComponent<RigidBody>())
	{
		enemyWithPathfinding->getComponents<RigidBody>()[0]->setLinearDamping(0.5f);
	}

	if (enemyStatic->hasComponent<RigidBody>())
	{
		enemyStatic->getComponents<RigidBody>().at(0)->setCanRotate(true);
	}
	else

	if (enemyWithCollider->hasComponent<RigidBody>())
	{
		enemyWithCollider->getComponents<RigidBody>().at(0)->setCanRotate(true);
	}
	scene->addGameObject(enemyMoving);
	scene->addGameObject(enemyStatic);
	scene->addGameObject(enemyWithCollider);
	scene->addGameObject(enemyWithPathfinding);


	GameObject* level2 = new GameObject;
	level2->addComponent<DemoLevel2Behaviour>();

	scene->addGameObject(level2);

	sceneManager.requestSceneChange("DemoScene2");

	mPlayerPositionSet = true;

	//saveGame();
}

void DemoManagerBehaviourScript::createStressTest() {
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene* scene = sceneManager.createScene("DemoStressTest");
	if (scene == nullptr)
	{
		exit(1);
	}

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setBackgroundColor(Color(0, 0, 0));

	camera->setRenderOrder(0);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene->addGameObject(camera);

	GameObject* playerObject =
		EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("Player").at(0);
	if (playerObject == nullptr)
	{
		std::cout << "Player not found" << std::endl;
		return;
	}
	playerObject->setTransform(Transform(Vector2(40, 40)));


	FSConverter fsconverter;
	std::string path = fsconverter.getResourcePath("LevelDefs/demoStressTest.json");
	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelCreatorBehaviourScript().createLevel(scene, mTileMapData);

	GameObject* spawner = new GameObject();
    spawner->addComponent<DemoBulletSpawner>();
	Transform transform;
	transform.position = Vector2(100, 100);
	spawner->setTransform(transform);
    scene->addGameObject(spawner);

	sceneManager.requestSceneChange("DemoStressTest");
}

void DemoManagerBehaviourScript::nextScene(const std::string& aSceneName)
{
	if (aSceneName == "2")
	{
		createSecondScene();
	}
	else if (aSceneName == "3")
	{
		createStressTest();
	}
}

void DemoManagerBehaviourScript::onStart()
{
	std::cout << "DemoInitBehaviourScript::onStart()" << std::endl;

	mCurrentScene = 0;
	createFirstScene();
	// createSecondScene();
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

	handleSaveGame();

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

void DemoManagerBehaviourScript::handleSaveGame()
{
	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_J))
	{

		saveGame();
	}

	if (input.GetKeyDown(Key::Key_K))
	{
		loadGame();
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

	sg.store();
}

void DemoManagerBehaviourScript::loadGame()
{
	SaveGame sg{"saves/newSave.json"};

	float playerX;
	float playerY;
	float playerRotation;
	float playerScaleX;
	float playerScaleY;

	try
	{
		playerX = sg.getFloatField("PlayerX").getValue();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		playerY = sg.getFloatField("PlayerY").getValue();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		playerRotation = sg.getFloatField("PlayerRotation").getValue();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		playerScaleX = sg.getFloatField("PlayerScaleX").getValue();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		playerScaleY = sg.getFloatField("PlayerScaleY").getValue();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

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
			Transform playerPos = (*playerIt)->getTransform();
			playerPos.position.x = playerX;
			playerPos.position.y = playerY;
			playerPos.rotation = playerRotation;
			playerPos.scale.x = playerScaleX;
			playerPos.scale.y = playerScaleY;

			(*playerIt)->setTransform(playerPos);
		}
	}
}
