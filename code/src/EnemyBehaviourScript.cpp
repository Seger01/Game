#include "EnemyBehaviourScript.h"
#include "BulletBehaviourScript.h"

EnemyBehaviourScript::EnemyBehaviourScript(float aHealth) : mHealth(aHealth) {
}

void EnemyBehaviourScript::onStart() {
    mIsDead = false;
}

void EnemyBehaviourScript::onUpdate() {
}

void EnemyBehaviourScript::onCollide(GameObject* aGameObject) {
    if (mIsDead) {
        return;
    }

    if (aGameObject->getTag() == "Bullet") {
        BulletBehaviourScript* bullet = aGameObject->getComponents<BulletBehaviourScript>().at(0);
        if (bullet != nullptr) {
            takeDamage(bullet->getDamage());
        }
        else{
            std::runtime_error("BulletBehaviourScript not found in EnemyBehaviourScript::onCollide");
        }
    }
}

void EnemyBehaviourScript::toggleAnimaionEnabled() {
}

void EnemyBehaviourScript::setAnimationActive(std::string aAnimationTag, bool aState) {
}

void EnemyBehaviourScript::deactivateAllAnimations() {
}

void EnemyBehaviourScript::setFlipX(bool aState) {
}

void EnemyBehaviourScript::setFlipY(bool aState) {
}

void EnemyBehaviourScript::takeDamage(float aDamage) {
    if (mHealth <= 0) {
        onDeath();
    }
    else {
        mHealth -= aDamage;
    }
}

void EnemyBehaviourScript::onDeath()
{
    if (mIsDead) {
        return;
    }
    mIsDead = true;

    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    if (mGameObject != nullptr) {
        std::cout << "Removing GameObject: " << mGameObject->getTag() << std::endl;
        sceneManager.getCurrentScene()->requestGameObjectRemoval(mGameObject);
    } 
    else {
        std::cerr << "Error: mGameObject is already null!" << std::endl;
    }
}