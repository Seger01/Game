#include "MainMenuPrefab.h"

GameObject* MainMenuPrefabFactory::createMainMenuPrefab() {
    GameObject* mainMenuPrefab = new GameObject;
    setTag(mainMenuPrefab);
    return mainMenuPrefab;
}

void MainMenuPrefabFactory::setTag(GameObject* gameObject) {
    gameObject->setTag("MainMenu");
}