#include "DemoLevel2Behaviour.h"
#include <EngineBravo.h>
#include <Animation.h>
#include <EnemyBehaviourScript.h>
#include <Input.h>

DemoLevel2Behaviour::DemoLevel2Behaviour() : mMovingUp(true), mInitialY(0.0f) {}

void DemoLevel2Behaviour::onStart() {
    mGameObject->setTag("DemoLevel2");

    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
    if (enemy != nullptr) {
        mInitialY = enemy->getTransform().position.y;
        if (enemy->hasComponent<RigidBody>()) {
            enemy->getComponents<RigidBody>()[0]->setActive(false);
        }
    }

    //rotateEnemy();

    GameObject* enemyStatic = scene->getGameObjectsWithTag("EnemyStatic")[0];
    if (enemyStatic != nullptr) {
        if (enemyStatic->hasComponent<EnemyBehaviourScript>()) {
            enemyStatic->getComponents<EnemyBehaviourScript>()[0]->deactivateAllAnimations();
        }
    }
}

void DemoLevel2Behaviour::onUpdate() {
    moveEnemy();
    //scaleEnemy();
    rotateEnemy();
}

void DemoLevel2Behaviour::onCollide(GameObject* aGameObject) {

}

void DemoLevel2Behaviour::moveEnemy() {
    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();
    Input& input = Input::getInstance();

    if (input.GetKeyDown(Key::Key_PageUp)) {
        Time::timeDilation = Time::timeDilation + 0.1f;
    }

    if (input.GetKeyDown(Key::Key_PageDown)) {
        Time::timeDilation = Time::timeDilation - 0.1f;
    }

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
    if (enemy == nullptr) {
        std::cout << "Enemy not found" << std::endl;
        return;
    }

    Transform transform = enemy->getTransform();

    if (mMovingUp) {
        transform.position.y += 10.0f * Time::deltaTime;
        if (transform.position.y >= mInitialY + 20.0f) {
            mMovingUp = false;
        }
    } else {
        transform.position.y -= 10.0f * Time::deltaTime;
        if (transform.position.y <= mInitialY - 20.0f) {
            mMovingUp = true;
        }
    }
    enemy->getComponentsWithTag<Animation>("enemyWalking")[0]->setActive(true);
    enemy->getComponentsWithTag<Sprite>("idleSprite")[0]->setActive(false);

    enemy->setTransform(transform);
}

void DemoLevel2Behaviour::scaleEnemy() {
    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyStatic")[0];
    if (enemy == nullptr) {
        std::cout << "Enemy not found" << std::endl;
        return;
    }

    Transform transform = enemy->getTransform();
    static bool scalingUp = true;

    if (scalingUp) {
        transform.scale.x += 0.01f;
        transform.scale.y += 0.01f;
        if (transform.scale.x >= 1.5f) {
            scalingUp = false;
        }
    } else {
        transform.scale.x -= 0.01f;
        transform.scale.y -= 0.01f;
        if (transform.scale.x <= 0.5f) {
            scalingUp = true;
        }
    }

    enemy->setTransform(transform);
}

void DemoLevel2Behaviour::rotateEnemy() {
    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyStatic")[0];
    if (enemy == nullptr) {
        std::cout << "Enemy not found" << std::endl;
        return;
    }
    Transform transform = enemy->getTransform();
    std::cout << "Initial rotatation: " << transform.rotation << std::endl;
    //transform.rotate(1000.0f * Time::deltaTime);
    transform.rotate(1.0f);
    std::cout << "Rotatation after update: " << transform.rotation << std::endl;
    enemy->setTransform(transform);
    std::cout << "Rotatation after update: " << enemy->getTransform().rotation << std::endl;
    //std::cout << "Deltatime: " << Time::deltaTime << std::endl;
}