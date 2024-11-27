#pragma once
#include <GameObject.h>
#include <LevelManagerBehaviourScript.h>
#include <LevelCreatorBehaviourScript.h>

class LevelManagerFactory {
public:
    static GameObject* createLevelManagerPrefab();

private:
    static void addBehaviourScripts(GameObject* gameObject);
    static void setTag(GameObject* gameObject);
};