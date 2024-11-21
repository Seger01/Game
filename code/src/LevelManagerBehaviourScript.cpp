#include "LevelManagerBehaviourScript.h"
#include <iostream>
#include <EngineBravo.h>
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>
#include "LevelCreatorBehaviourScript.h"

void LevelManagerBehaviourScript::onStart() {
    mCurrentLevel = 1;
    createLevelCreator();
}

void LevelManagerBehaviourScript::onUpdate() {
}

void LevelManagerBehaviourScript::doneWithCurrentLevel() {
    mCurrentLevel++;
    //createLevelCreator();

    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();
    if (scene->getGameObjectsWithTag("LevelCreator").size() > 0) {
        if (scene->getGameObjectsWithTag("LevelCreator")[0]->hasComponent<LevelCreatorBehaviourScript>()) {
            auto Components = scene->getGameObjectsWithTag("LevelCreator")[0]->getComponents<LevelCreatorBehaviourScript>();
            if (!Components.empty()) {
                LevelCreatorBehaviourScript* Component = Components[0];
                if (mCurrentLevel == 1) {
                    Component->createLevel1();
                }
                else if (mCurrentLevel == 2) {
                    Component->createLevel2();
                }
                else if (mCurrentLevel == 3) {
                    Component->createLevel3();
                }
                else {
                    std::cerr << "Level not found in LevelManagerBehaviourScript.cpp\n";
                }
            }
        }
    }
    else {
        std::cerr << "LevelCreator not found in scene (LevelManagerBehaviourScript.cpp)\n";
    }
    //TODO: Load next level
}

void LevelManagerBehaviourScript::createLevelCreator() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();

    Scene* scene = sceneManager.getCurrentScene();
    GameObject* LevelCreatorObject = new GameObject;
    LevelCreatorObject->addComponent<LevelCreatorBehaviourScript>();
    LevelCreatorObject->setTag("LevelCreator");

    scene->addPersistentGameObject(LevelCreatorObject);
}