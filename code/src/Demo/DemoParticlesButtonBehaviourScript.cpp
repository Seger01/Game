#include "DemoParticlesButtonBehaviourScript.h"
#include <iostream>
#include <Sprite.h>

DemoParticlesButtonBehaviourScript::DemoParticlesButtonBehaviourScript() {}

void DemoParticlesButtonBehaviourScript::onStart() {
    mButtonPressed = false;
}

void DemoParticlesButtonBehaviourScript::onUpdate() {

}

void DemoParticlesButtonBehaviourScript::onCollide(GameObject* aGameObject) {
    if (aGameObject == nullptr) {
        return;
    }
    if (aGameObject->getTag() == "Player") {
        updateButtonState();
    }
}

void DemoParticlesButtonBehaviourScript::updateButtonState() {
    if (!mButtonPressed) {
        for (Component* component : mGameObject->getComponents<Sprite>()) {
            if (component->getTag() == "ButtonDownSprite") {
                component->setActive(true);
            }
            else if (component->getTag() == "ButtonUpSprite") {
                component->setActive(false);
            }
        }
        launchParticles();
        mButtonPressed = true;
    }
    else {
        for (Component* component : mGameObject->getComponents<Sprite>()) {
            if (component->getTag() == "ButtonDownSprite") {
                component->setActive(false);
            }
            else if (component->getTag() == "ButtonUpSprite") {
                component->setActive(true);
            }
        }
        mButtonPressed = false;
    }
}

void DemoParticlesButtonBehaviourScript::launchParticles() {
    std::cout << "Particles launched" << std::endl;
}
