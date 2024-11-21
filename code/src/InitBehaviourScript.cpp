#include "InitBehaviourScript.h"
#include <iostream>
#include <EngineBravo.h>
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>
#include "LevelManagerBehaviourScript.h"

void InitBehaviourScript::onStart() {
    createLevelManager();
}

void InitBehaviourScript::onUpdate() {
    std::cout << "Hello, World!" << std::endl;
}

void InitBehaviourScript::createLevelManager() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();

    Scene* scene = sceneManager.createScene("PersistentManagementScene");
    GameObject* LevelManagerObject = new GameObject;
    LevelManagerObject->addComponent<LevelManagerBehaviourScript>();

    scene->addPersistentGameObject(LevelManagerObject);

    int cameraID = scene->addCamera();
    scene->setActiveCamera(cameraID);

    scene->getActiveCamera().setTransform(Transform(Vector2(80, 96)));
    scene->getActiveCamera().setWidth(16 * 30);
    scene->getActiveCamera().setHeight(9 * 30);

    sceneManager.requestSceneChange("PersistentManagementScene");
}
