#include "MainMenuBehaviourScript.h"

#include "DemoInitBehaviourScript.h"
#include "EngineBravo.h"
#include "LevelManagerBehaviourScript.h"

MainMenuBehaviourScript::MainMenuBehaviourScript() {}

MainMenuBehaviourScript::~MainMenuBehaviourScript() {}

void MainMenuBehaviourScript::onStart() {
    for (GameObject* button :
         EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("PlayButton")) {
        Button* buttonObject = dynamic_cast<Button*>(button);
        buttonObject->setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onPlayRelease, this));
    }
    for (GameObject* button :
         EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("MultiplayerButton")) {
        Button* buttonObject = dynamic_cast<Button*>(button);
        buttonObject->setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onMultiplayerRelease, this));
    }
    for (GameObject* button :
         EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("DemoButton")) {
        Button* buttonObject = dynamic_cast<Button*>(button);
        buttonObject->setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onDemoRelease, this));
    }
    for (GameObject* button :
         EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("ExitButton")) {
        Button* buttonObject = dynamic_cast<Button*>(button);
        buttonObject->setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onExitRelease, this));
    }
}

void MainMenuBehaviourScript::onUpdate() {}

void MainMenuBehaviourScript::onPlayRelease() {
    std::cout << "Wanted to play the game" << std::endl;
    for (GameObject* object :
         EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager")) {
        if (object->hasComponent<LevelManagerBehaviourScript>()) {
            object->getComponents<LevelManagerBehaviourScript>()[0]->beginGame();
        }
    }
}

void MainMenuBehaviourScript::onMultiplayerRelease() { std::cout << "Wanted to multiplayer" << std::endl; }

void MainMenuBehaviourScript::onDemoRelease() {
    GameObject* demoobject = new GameObject;
    demoobject->addComponent<DemoInitBehaviourScript>();

    Scene* scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();

    std::cout << "Current scene: " << scene->getName() << std::endl;

    scene->addGameObject(demoobject);

    std::cout << "Wanted to play demo" << std::endl;
}

void MainMenuBehaviourScript::onExitRelease() { std::cout << "adfljasdflkjafds to exit game" << std::endl; }
