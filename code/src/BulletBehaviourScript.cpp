#include "BulletBehaviourScript.h"

void BulletBehaviourScript::onStart() {}

void BulletBehaviourScript::onUpdate() {}

void BulletBehaviourScript::onCollide(GameObject* aGameObject) {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    if (aGameObject->getTag() != "Player") {
        sceneManager.getCurrentScene()->requestGameObjectRemoval(mGameObject);
    }
}