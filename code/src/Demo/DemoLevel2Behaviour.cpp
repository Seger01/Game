#include "DemoLevel2Behaviour.h"
#include <EngineBravo.h>

DemoLevel2Behaviour::DemoLevel2Behaviour() : mMovingUp(true), mInitialY(0.0f) {}

void DemoLevel2Behaviour::onStart() {
    mGameObject->setTag("DemoLevel2");

    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
    if (enemy != nullptr) {
        mInitialY = enemy->getTransform().position.y;
    }
    rotateEnemy();
}

void DemoLevel2Behaviour::onUpdate() {
    moveEnemy();
    //scaleEnemy();
}

void DemoLevel2Behaviour::onCollide(GameObject* aGameObject) {
}

void DemoLevel2Behaviour::moveEnemy() {
    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
    if (enemy == nullptr) {
        std::cout << "Enemy not found" << std::endl;
        return;
    }

    Transform transform = enemy->getTransform();
    if (mMovingUp) {
        transform.position.y += 1.0f;
        if (transform.position.y >= mInitialY + 20.0f) {
            mMovingUp = false;
        }
    } else {
        transform.position.y -= 1.0f;
        if (transform.position.y <= mInitialY - 20.0f) {
            mMovingUp = true;
        }
    }
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

    RigidBody* rigidBody = enemy->getComponents<RigidBody>()[0];
    if (rigidBody == nullptr) {
        std::cout << "RigidBody not found" << std::endl;
        return;
    }
    else {
        rigidBody->addTorque(500.0f);
    }
}