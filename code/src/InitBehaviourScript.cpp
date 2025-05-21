#include "InitBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
#include "LevelManagerPrefab.h"
#include "MainMenuPrefab.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Scene.h>
#include <iostream>

void InitBehaviourScript::onStart() { createLevelManager(); }

void InitBehaviourScript::onUpdate() {}

void InitBehaviourScript::createLevelManager()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();

	GameObject* LevelManagerObject = LevelManagerFactory().createLevelManagerPrefab();

	scene.addPersistentGameObject(LevelManagerObject);

	createMainMenu();
}

void InitBehaviourScript::createMainMenu()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.createScene("MainMenuScene");

	int menuStartX = 240 + 13;
	int menuStartY = 135 + 5;

	GameObject* MainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, &scene, "Play", "PlayButton", "Play", menuStartX,
												menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, &scene, "Multiplayer", "MultiplayerButton",
												"Multiplayer", menuStartX, menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, &scene, "Demo", "DemoButton", "Demo", menuStartX,
												menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, &scene, "Demo Multiplayer", "DemoMultiButton",
												"Demo Multiplayer", menuStartX, menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, &scene, "Exit", "ExitButton", "Exit", menuStartX,
												menuStartY);

	scene.addGameObject(MainMenuObject);

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2((16 * 30) / 2, (9 * 30) / 2)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	scene.addGameObject(camera);

	sceneManager.requestSceneChange("MainMenuScene");
}
