#include "LevelCreatorBehaviourScript.h"
#include <iostream>
#include <EngineBravo.h>
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>
#include <TileMapParser.h>
#include <FSConverter.h>
#include <Sprite.h>
#include <BoxCollider.h>
#include <RigidBody.h>
#include <SpriteDef.h>
#include "CanvasBehaviourScript.h"
#include <Text.h>
//#include <FPSCounterBehaviourScript.h>
#include <AudioSource.h>


void LevelCreatorBehaviourScript::onStart() {
    createLevel1();
}

void LevelCreatorBehaviourScript::onUpdate() {

}

void LevelCreatorBehaviourScript::createLevel1() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();

    Scene* scene = sceneManager.createScene("Level-1");
    if (scene == nullptr) {
        exit(1);
    }

    int cameraID = scene->addCamera();
    scene->setActiveCamera(cameraID);

    scene->getActiveCamera().setTransform(Transform(Vector2(80, 96)));
    scene->getActiveCamera().setWidth(16 * 30);
    scene->getActiveCamera().setHeight(9 * 30);


    FSConverter fsConverter;
    std::string path = fsConverter.getResourcePath("LevelDefs/levelwithcollision.json");

    TileMapParser tileMapParser(path);
    tileMapParser.parse();
    const TileMapData& tileMapData = tileMapParser.getTileMapData();

    createLevel(scene, tileMapData);

    sceneManager.requestSceneChange("Level-1");
}

void LevelCreatorBehaviourScript::createLevel2() {

}

void LevelCreatorBehaviourScript::createLevel3() {

}

void LevelCreatorBehaviourScript::createPlayer() {

}

void LevelCreatorBehaviourScript::createEnemy() {

}

void LevelCreatorBehaviourScript::createBoss() {

}

void LevelCreatorBehaviourScript::createLevel(Scene* scene, const TileMapData& tileMapData) {
    if (scene == nullptr) {
        std::runtime_error("Scene is null in LevelCreatorBehaviourScript::createLevel");
    }

    EngineBravo& engine = EngineBravo::getInstance();


    for (const auto& roomTrigger : tileMapData.mRoomTriggers) {
        // Collect enemy spawns for this room
        std::vector<SpawnPoint> enemySpawns;
        for (const auto& spawnPoint : tileMapData.mSpawnPoints) {
            if (spawnPoint.isEnemySpawn && spawnPoint.roomID == roomTrigger.roomID) {
                enemySpawns.push_back(spawnPoint);
            }
        }

        GameObject* roomObject = new GameObject;
        roomObject->addComponent(new RoomBehaviourScript(roomTrigger.roomID, enemySpawns));
        BoxCollider* boxCollider = new BoxCollider();
        Transform transform;
        transform.position.x = roomTrigger.x;
        transform.position.y = roomTrigger.y;
        boxCollider->setTransform(transform);
        boxCollider->setWidth(roomTrigger.mWidth);
        boxCollider->setHeight(roomTrigger.mHeight);
        boxCollider->setTrigger(true);
        roomObject->addComponent(boxCollider);
        RigidBody* rigidBody = new RigidBody();
        rigidBody->setTransform(transform);
        roomObject->addComponent(rigidBody);
        roomObject->setName("Roomtrigger");
        scene->addGameObject(roomObject);
    }

    GameObject* canvasObject = new GameObject;

    canvasObject->addComponent<CanvasBehaviourScript>();

    scene->addGameObject(canvasObject);

    // GameObject* textObject =
    //     new Text("FPS: ", "font/SupremeSpike.otf", Color(86, 140, 100), Vector2(0, -30), Vector2(1, 1));
    // Text* text = dynamic_cast<Text*>(textObject);
    // text->setLayer(5);

    // text->addComponent<FPSCounterBehaviourScript>();

    // int textWidth = 0;
    // int textHeight = 0;
    // if (!engine.getRenderSystem().getTextSize(text->getFont(), text->getText(), textWidth, textHeight,
    //                                           text->getScale())) {
    //     std::cout << "Failed to get text size for FPS counter.\n";
    // }

    // Sprite* textBackground = engine.getResourceManager().createSprite(textBackgroundDef);
    // textBackground->setLayer(3);
    // textBackground->setWidth(10);
    // textBackground->setHeight(10);

    // text->addComponent(textBackground);

    // scene->addGameObject(text);

    GameObject* musicObject = new GameObject;

    // Add music
    AudioSource* music = new AudioSource("Audio/music.wav", true);
    music->setPlayOnWake(true);
    music->setVolume(10);
    music->setXDirection(0);
    musicObject->addComponent(music);

    scene->addGameObject(musicObject);

    // Assuming tileMapData is a const reference to TileMapData
    for (size_t layerIndex = 0; layerIndex < tileMapData.mLayers.size(); ++layerIndex) {
        bool isDoorsLayer = (tileMapData.mLayerNames[layerIndex] == "Doors");
        // Access rows within the layer by index
        for (size_t rowIndex = 0; rowIndex < tileMapData.mLayers[layerIndex].size(); ++rowIndex) {
            // Access each tile in the row by index
            for (size_t colIndex = 0; colIndex < tileMapData.mLayers[layerIndex][rowIndex].size(); ++colIndex) {
                int tile = tileMapData.mLayers[layerIndex][rowIndex][colIndex];
                if (tile != 0) {
                    // Check if the tile exists in mTileInfoMap (read-only)
                    auto it = tileMapData.mTileInfoMap.find(tile);
                    if (it != tileMapData.mTileInfoMap.end()) {
                        const TileInfo& tileInfo = it->second; // Access as const

                        SpriteDef spriteDef = {tileInfo.mTilesetName,
                                               Rect{tileInfo.mCoordinates.first, tileInfo.mCoordinates.second, 16, 16},
                                               16, 16};

                        GameObject* gameObject = new GameObject;

                        Transform objectTransform;
                        objectTransform.position.x = static_cast<int>(colIndex * 16);
                        objectTransform.position.y = static_cast<int>(rowIndex * 16);
                        gameObject->setTransform(objectTransform);

                        // Add a Sprite component to the GameObject
                        Sprite* sprite = engine.getResourceManager().createSprite(spriteDef);

                        sprite->setLayer(layerIndex);

                        gameObject->addComponent(sprite);

                        // Add BoxCollider components to the GameObject
                        for (const auto& collider : tileInfo.mColliders) {
                            BoxCollider* boxCollider = new BoxCollider();
                            Transform transform;
                            transform.position.x = collider.x;
                            transform.position.y = collider.y;
                            boxCollider->setTransform(transform);
                            boxCollider->setWidth(collider.mWidth);
                            boxCollider->setHeight(collider.mHeight);
                            if (isDoorsLayer) {
                                boxCollider->setActive(false);
                            }
                            gameObject->addComponent(boxCollider);
                        }

                        if (!tileInfo.mColliders.empty()) {
                            RigidBody* rigidBody = new RigidBody();
                            rigidBody->setTransform(objectTransform);
                            if (isDoorsLayer) {
                                if (rigidBody != nullptr) {
                                    rigidBody->setActive(false);
                                }
                            }
                            gameObject->addComponent(rigidBody);
                            gameObject->setName("Tile");
                        }
                        if (isDoorsLayer) {
                            gameObject->setTag("Door");
                        }
                        scene->addGameObject(gameObject);

                    } else {
                        // Handle the case where tileId does not exist in the map
                        std::cout << "Tile ID " << tile << " not found in mTileInfoMap.\n";
                    }
                }
            }
        }
    }
}