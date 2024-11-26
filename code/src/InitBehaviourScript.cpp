#include "InitBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
#include "MainMenuPrefab.h"
#include "LevelManagerPrefab.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <iostream>

void InitBehaviourScript::onStart() { createLevelManager(); }

void InitBehaviourScript::onUpdate() {
  
}

void InitBehaviourScript::createLevelManager() {
  EngineBravo &engine = EngineBravo::getInstance();
  SceneManager &sceneManager = engine.getSceneManager();
  Scene *scene = sceneManager.getCurrentScene();


  GameObject *LevelManagerObject = LevelManagerFactory().createLevelManagerPrefab();

  scene->addPersistentGameObject(LevelManagerObject);

  createMainMenu();
  //LevelManagerBehaviourScript* levelManager = LevelManagerObject->getComponents<LevelManagerBehaviourScript>()[0];
  //levelManager->beginGame();
}

void InitBehaviourScript::createMainMenu() {
  EngineBravo &engine = EngineBravo::getInstance();
  SceneManager &sceneManager = engine.getSceneManager();
  Scene *scene = sceneManager.createScene("MainMenuScene");

  GameObject *MainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();

  scene->addGameObject(MainMenuObject);

  int cameraID = scene->addCamera();
  scene->setActiveCamera(cameraID);

  scene->getActiveCamera().setTransform(Transform(Vector2(80, 96)));
  scene->getActiveCamera().setWidth(16 * 30);
  scene->getActiveCamera().setHeight(9 * 30);
  
  sceneManager.requestSceneChange("MainMenuScene");
}
