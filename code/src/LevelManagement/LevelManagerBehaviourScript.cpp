#include "LevelManagerBehaviourScript.h"
#include "LevelCreatorBehaviourScript.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <iostream>

void LevelManagerBehaviourScript::onStart() {
}

void LevelManagerBehaviourScript::onUpdate() {}

void LevelManagerBehaviourScript::beginGame() {
  mGameObject->getComponents<LevelCreatorBehaviourScript>().at(0)->createLevel1();
}

void LevelManagerBehaviourScript::beginDemoNetworkingGame() {
  mGameObject->getComponents<LevelCreatorBehaviourScript>().at(0)->createDemoNetworkingLevel();
}

void LevelManagerBehaviourScript::doneWithCurrentLevel() {
  mCurrentLevel++;

  EngineBravo &engine = EngineBravo::getInstance();
  SceneManager &sceneManager = engine.getSceneManager();
  Scene *scene = sceneManager.getCurrentScene();
  if (scene->getGameObjectsWithTag("LevelCreator").size() > 0) {
    if (scene->getGameObjectsWithTag("LevelCreator")[0]
            ->hasComponent<LevelCreatorBehaviourScript>()) {
      auto Components = scene->getGameObjectsWithTag("LevelCreator")[0]
                            ->getComponents<LevelCreatorBehaviourScript>();
      if (!Components.empty()) {
        LevelCreatorBehaviourScript *Component = Components[0];
        if (mCurrentLevel == 1) {
          Component->createLevel1();
        } else if (mCurrentLevel == 2) {
          Component->createLevel2();
        } else if (mCurrentLevel == 3) {
          Component->createLevel3();
        } else {
          std::cerr << "Level not found in LevelManagerBehaviourScript.cpp\n";
        }
      }
    }
  } else {
    std::cerr << "LevelCreator not found in scene "
                 "(LevelManagerBehaviourScript.cpp)\n";
  }
  // TODO: Load next level
}