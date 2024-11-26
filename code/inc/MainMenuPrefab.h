#pragma once
#include <GameObject.h>


class MainMenuPrefabFactory {
public:
    static GameObject* createMainMenuPrefab();

private:
    static void setTag(GameObject* gameObject);
};

