#include "LevelCreatorBehaviourScript.h"
#include "CanvasBehaviourScript.h"
#include "EnemyPrefab.h"
#include "LevelEndBehaviourScript.h"
#include "NetworkDemoSceneBehaviour.h"
#include "NetworkObject.h"
#include "PlayerPrefab.h"
#include "RoomBehaviourScript.h"
#include <AudioSource.h>
#include <BoxCollider.h>
#include <CircleCollider.h>
#include <EngineBravo.h>
#include <FSConverter.h>
#include <GameObject.h>
#include <LevelBuilder.h>
#include <RigidBody.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <Text.h>
#include <TileMapParser.h>
#include <Transform.h>
#include <algorithm>
#include <iostream>

void LevelCreatorBehaviourScript::onStart() {}

void LevelCreatorBehaviourScript::onUpdate()
{
	if (!mPlayerPositionSet)
	{
		EngineBravo& engine = EngineBravo::getInstance();
		SceneManager& sceneManager = engine.getSceneManager();
		Scene& currentScene = sceneManager.getCurrentScene();

		std::vector<std::reference_wrapper<GameObject>> persistentObjects = currentScene.getPersistentGameObjects();
		auto playerIt = std::find_if(persistentObjects.begin(), persistentObjects.end(),
									 [](GameObject& obj) { return obj.getTag() == "Player"; });

		if (playerIt != persistentObjects.end())
		{
			setPlayerStartPosition(&currentScene, mTileMapData);
			mPlayerPositionSet = true; // Set the flag to true
		}
	}
}

void LevelCreatorBehaviourScript::createLevel1()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene& scene = sceneManager.createScene("Level-1");

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene.addGameObject(camera);

	std::string path = mFsConverter.getResourcePath("LevelDefs/levelwithcollision.json");

	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelBuilder levelBuilder;
	levelBuilder.createLevel(&scene, mTileMapData);

	// Add specific components
	addRoomEntries(&scene, mTileMapData);
	addLevelEndTriggers(&scene, mTileMapData);

	createPlayer(&scene, mTileMapData);
	sceneManager.requestSceneChange("Level-1");
	mPlayerPositionSet = false;
}

void LevelCreatorBehaviourScript::createLevel2()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene& scene = sceneManager.createScene("Level-2");

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene.addGameObject(camera);

	std::string path = mFsConverter.getResourcePath("LevelDefs/level2.json");

	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelBuilder levelBuilder;
	levelBuilder.createLevel(&scene, mTileMapData);

	// Add specific components
	addRoomEntries(&scene, mTileMapData);
	addLevelEndTriggers(&scene, mTileMapData);

	sceneManager.requestSceneChange("Level-2");
	mPlayerPositionSet = false;
}

void LevelCreatorBehaviourScript::createLevel3()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene& scene = sceneManager.createScene("Level-3");

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene.addGameObject(camera);

	std::string path = mFsConverter.getResourcePath("LevelDefs/level3.json");

	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	mTileMapData = tileMapParser.getTileMapData();

	LevelBuilder levelBuilder;
	levelBuilder.createLevel(&scene, mTileMapData);

	// Add specific components
	addRoomEntries(&scene, mTileMapData);
	addLevelEndTriggers(&scene, mTileMapData);

	sceneManager.requestSceneChange("Level-3");
	mPlayerPositionSet = false;
}

void LevelCreatorBehaviourScript::createDemoNetworkingLevel()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Scene& scene = sceneManager.createScene("DemoNetworkingLevel");

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	int width;
	int height;

	if (engine.getNetworkManager().isServer())
	{
		width = 22 * 16;
		height = 23 * 16;
	}
	else
	{
		width = 16 * 16;
		height = 9 * 16;
	}

	camera->setTransform(Transform(Vector2(11 * 16, 12 * 16)));
	camera->setWidth(width);
	camera->setHeight(height);

	scene.addGameObject(camera);

	std::string path = mFsConverter.getResourcePath("LevelDefs/networkDemoLevel.json");

	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	const TileMapData& tileMapData = tileMapParser.getTileMapData();

	LevelBuilder levelBuilder;
	levelBuilder.createLevel(&scene, tileMapData);

	// Add specific components
	addRoomEntries(&scene, tileMapData);
	addLevelEndTriggers(&scene, tileMapData);

	GameObject* sceneBehaviour = new GameObject;
	sceneBehaviour->setTag("SceneBehaviour");
	sceneBehaviour->addComponent(new NetworkDemoSceneBehaviour());
	scene.addGameObject(sceneBehaviour);

	sceneManager.requestSceneChange("DemoNetworkingLevel");
}

void LevelCreatorBehaviourScript::createPlayer(Scene* scene, const TileMapData& tileMapData)
{
	if (scene == nullptr)
	{
		std::runtime_error("Scene is null in LevelCreatorBehaviourScript::createPlayer");
	}

	GameObject* defaultPlayerPrefab = PlayerPrefabFactory().createPlayerPrefab();

	scene->addPersistentGameObject(defaultPlayerPrefab);
}

void LevelCreatorBehaviourScript::setPlayerStartPosition(Scene* scene, const TileMapData& tileMapData)
{
	if (tileMapData.mMapObjects.empty())
	{
		// throw std::runtime_error("No map objects found in LevelCreatorBehaviourScript::setPlayerStartPosition");
		return;
	}

	for (const auto& mapObject : tileMapData.mMapObjects)
	{
		if (mapObject.properties.find("isPlayerSpawn") != mapObject.properties.end() &&
			mapObject.properties.at("isPlayerSpawn") == "true")
		{
			// std::cout << "Setting player position to " << mapObject.x << ", " << mapObject.y << std::endl;

			std::vector<std::reference_wrapper<GameObject>> persistentObjects = scene->getPersistentGameObjects();
			// std::cout << "Number of persistent objects: " << persistentObjects.size() << std::endl;

			auto playerIt = std::find_if(persistentObjects.begin(), persistentObjects.end(),
										 [](GameObject& obj) { return obj.getTag() == "Player"; });

			if (playerIt == persistentObjects.end())
			{
				throw std::runtime_error("No player found in LevelCreatorBehaviourScript::setPlayerStartPosition");
			}

			Transform transform;
			transform.position.x = mapObject.x;
			transform.position.y = mapObject.y;

			(*playerIt).get().setTransform(transform);
			// std::cout << "Player position set to " << transform.position.x << ", " << transform.position.y <<
			// std::endl;
		}
	}
}

void LevelCreatorBehaviourScript::addRoomEntries(Scene* scene, const TileMapData& tileMapData)
{
    for (const auto& mapObject : tileMapData.mMapObjects)
    {
        if (mapObject.type == "room_entry")
        {
            std::vector<MapObject> enemySpawns;
            for (const auto& spawnPoint : tileMapData.mMapObjects)
            {
                if (spawnPoint.properties.find("isEnemySpawn") != spawnPoint.properties.end() &&
                    spawnPoint.properties.at("isEnemySpawn") == "true" &&
                    spawnPoint.properties.at("roomID") == mapObject.properties.at("roomID"))
                {
                    enemySpawns.push_back(spawnPoint);
                }
            }
        
            if (!scene->getGameObjectsWithTag("RoomTrigger").empty())
            {
                std::vector<std::reference_wrapper<GameObject>> roomTriggers = scene->getGameObjectsWithTag("RoomTrigger");
                for (auto& roomTrigger : roomTriggers)
                {
                    if (roomTrigger.get().getName() == "RoomTrigger" + mapObject.properties.at("roomID"))
                    {
                        roomTrigger.get().addComponent(new RoomBehaviourScript(mapObject.properties.at("roomID"), enemySpawns));
                    }
                }
            }
        }
    }
}

void LevelCreatorBehaviourScript::addLevelEndTriggers(Scene* scene, const TileMapData& tileMapData)
{
	for (const auto& mapObject : tileMapData.mMapObjects)
	{
		if (mapObject.type == "LevelEndTrigger")
		{
			if (!scene->getGameObjectsWithTag("LevelEnd").empty())
			{
				GameObject& levelEndObject = scene->getGameObjectsWithTag("LevelEnd").back().get();
				levelEndObject.addComponent(new LevelEndBehaviourScript());
			}
		}
	}
}