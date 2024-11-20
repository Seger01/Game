#include "LevelManagerBehaviourScript.h"
#include <iostream>
#include <EngineBravo.h>
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>
#include "LevelCreatorBehaviourScript.h"

void LevelManagerBehaviourScript::onStart() {
    createLevelCreator();
}

void LevelManagerBehaviourScript::onUpdate() {
}

void LevelManagerBehaviourScript::doneWithCurrentLevel() {
    mCurrentLevel++;
    //createLevelCreator();
    //TODO: Load next level
}

void LevelManagerBehaviourScript::createLevelCreator() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();

    Scene* scene = sceneManager.getCurrentScene();
    GameObject* LevelCreatorObject = new GameObject;
    LevelCreatorObject->addComponent<LevelCreatorBehaviourScript>();

    scene->addGameObject(LevelCreatorObject);
}