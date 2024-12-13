#include "LevelCreatorBehaviourScript.h"
#include "CanvasBehaviourScript.h"
#include <BoxCollider.h>
#include <EngineBravo.h>
#include <FSConverter.h>
#include <GameObject.h>
#include <RigidBody.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <Text.h>
#include <TileMapParser.h>
#include <iostream>
// #include <FPSCounterBehaviourScript.h>
#include "LevelEndBehaviourScript.h"
#include "PlayerPrefab.h"
#include "RoomBehaviourScript.h"
#include <AudioSource.h>
#include <CircleCollider.h>
#include <Transform.h>
#include <algorithm>

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

	createLevel(&scene, mTileMapData);
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

	createLevel(&scene, mTileMapData);
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

	createLevel(&scene, mTileMapData);
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

	// scene->getActiveCamera().setTransform(Transform(Vector2(11 * 16, 12 * 16)));
	// scene->getActiveCamera().setWidth(width);
	// scene->getActiveCamera().setHeight(height);
	camera->setTransform(Transform(Vector2(11 * 16, 12 * 16)));
	camera->setWidth(width);
	camera->setHeight(height);

	scene.addGameObject(camera);

	std::string path = mFsConverter.getResourcePath("LevelDefs/networkDemoLevel.json");

	TileMapParser tileMapParser(path);
	tileMapParser.parse();
	const TileMapData& tileMapData = tileMapParser.getTileMapData();

	createLevel(&scene, tileMapData);
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

void LevelCreatorBehaviourScript::createEnemy() {}

void LevelCreatorBehaviourScript::createBoss() {}

void LevelCreatorBehaviourScript::createLevel(Scene* scene, const TileMapData& tileMapData)
{
	if (scene == nullptr)
	{
		throw std::runtime_error("Scene is null in LevelCreatorBehaviourScript::createLevel");
	}

	EngineBravo& engine = EngineBravo::getInstance();

	for (const auto& mapObject : tileMapData.mMapObjects)
	{
		if (!mapObject.type.empty())
		{
			std::string type = mapObject.type;
			if (type == "room_entry")
			{ // Collect enemy spawns for this room
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

				GameObject* roomObject = new GameObject;
				roomObject->addComponent(new RoomBehaviourScript(mapObject.properties.at("roomID"), enemySpawns));
				BoxCollider* boxCollider = new BoxCollider();
				Transform transform;
				transform.position.x = mapObject.x;
				transform.position.y = mapObject.y;
				boxCollider->setTransform(transform);
				boxCollider->setWidth(mapObject.width);
				boxCollider->setHeight(mapObject.height);
				boxCollider->setTrigger(true);
				roomObject->addComponent(boxCollider);
				RigidBody* rigidBody = new RigidBody();
				rigidBody->setTransform(transform);
				roomObject->addComponent(rigidBody);
				roomObject->setName("RoomTrigger");
				scene->addGameObject(roomObject);
			}

			// Add a trigger for the level end
			else if (type == "LevelEndTrigger")
			{
				std::cout << "Creating LevelEndTrigger" << std::endl;
				GameObject* levelEndObject = new GameObject;
				BoxCollider* boxCollider = new BoxCollider();
				Transform transform;
				transform.position.x = mapObject.x;
				transform.position.y = mapObject.y;
				boxCollider->setTransform(transform);
				boxCollider->setWidth(mapObject.width);
				boxCollider->setHeight(mapObject.height);
				boxCollider->setTrigger(true);
				levelEndObject->addComponent(boxCollider);
				RigidBody* rigidBody = new RigidBody();
				rigidBody->setTransform(transform);
				levelEndObject->addComponent(rigidBody);
				levelEndObject->setName("LevelEndTrigger");
				levelEndObject->setTag("LevelEnd");
				levelEndObject->addComponent(new LevelEndBehaviourScript());
				scene->addGameObject(levelEndObject);
			}
		}
	}

	GameObject* canvasObject = new GameObject;

	canvasObject->addComponent<CanvasBehaviourScript>();

	scene->addGameObject(canvasObject);

	GameObject* musicObject = new GameObject;

	// Add music
	AudioSource* music = new AudioSource("Audio/music.wav", true);
	music->setPlayOnWake(true);
	music->setVolume(10);
	music->setXDirection(0);
	musicObject->addComponent(music);

	scene->addGameObject(musicObject);

	// Assuming tileMapData is a const reference to TileMapData
	for (size_t layerIndex = 0; layerIndex < tileMapData.mLayers.size(); ++layerIndex)
	{
		bool isDoorsLayer = (tileMapData.mLayerNames[layerIndex] == "Doors");
		bool isGraphLayer = (tileMapData.mLayerNames[layerIndex] == "Graph");
		// Access rows within the layer by index
		for (size_t rowIndex = 0; rowIndex < tileMapData.mLayers[layerIndex].size(); ++rowIndex)
		{
			// Access each tile in the row by index
			for (size_t colIndex = 0; colIndex < tileMapData.mLayers[layerIndex][rowIndex].size(); ++colIndex)
			{
				int tile = tileMapData.mLayers[layerIndex][rowIndex][colIndex];
				if (tile != 0)
				{
					// Check if the tile exists in mTileInfoMap (read-only)
					auto it = tileMapData.mTileInfoMap.find(tile);
					if (it != tileMapData.mTileInfoMap.end())
					{
						const TileInfo& tileInfo = it->second; // Access as const

						SpriteDef spriteDef = {tileInfo.mTilesetName,
											   Rect{tileInfo.mCoordinates.first, tileInfo.mCoordinates.second, 16, 16},
											   16, 16};

						GameObject* gameObject = new GameObject;

						Transform objectTransform;
						objectTransform.position.x = static_cast<int>(colIndex * 16);
						objectTransform.position.y = static_cast<int>(rowIndex * 16);
						gameObject->setTransform(objectTransform);

						if (!isGraphLayer)
						{
							// Add a Sprite component to the GameObject
							Sprite* sprite = engine.getResourceManager().createSprite(spriteDef);

							sprite->setLayer(layerIndex);

							gameObject->addComponent(sprite);
						}
						// Add BoxCollider components to the GameObject
						for (const auto& collider : tileInfo.mColliders)
						{
							BoxCollider* boxCollider = new BoxCollider();
							Transform transform;
							transform.position.x = collider.x;
							transform.position.y = collider.y;
							boxCollider->setTransform(transform);
							boxCollider->setWidth(collider.mWidth + 0.1f);
							boxCollider->setHeight(collider.mHeight + 0.1f);
							boxCollider->setCollideCategory(1);
							boxCollider->setCollideWithCategory({1, 2, 3});
							if (isDoorsLayer)
							{
								boxCollider->setActive(false);
							}
							gameObject->addComponent(boxCollider);
						}

						if (!tileInfo.mColliders.empty())
						{
							RigidBody* rigidBody = new RigidBody();
							rigidBody->setTransform(objectTransform);
							if (isDoorsLayer)
							{
								if (rigidBody != nullptr)
								{
									rigidBody->setActive(false);
								}
							}
							rigidBody->setFriction(5.0f);
							gameObject->addComponent(rigidBody);
							gameObject->setName("Tile");
						}
						if (isDoorsLayer)
						{
							gameObject->setTag("Door");
						}
						scene->addGameObject(gameObject);
					}
					else
					{
						// Handle the case where tileId does not exist in the map
						std::cout << "Tile ID " << tile << " not found in mTileInfoMap.\n";
					}
				}
			}
		}
	}
}
