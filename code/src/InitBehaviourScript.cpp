#include "InitBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
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

  LevelManagerBehaviourScript* levelManager = LevelManagerObject->getComponents<LevelManagerBehaviourScript>()[0];
  levelManager->beginGame();
}
