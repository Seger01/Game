#include "DemoParticlesButtonBehaviourScript.h"
#include <iostream>
#include <Sprite.h>
#include <Particle.h>
#include <ParticleEmitter.h>
#include <ParticleSystem.h>
#include <Time.h>
#include <EngineBravo.h>
#include <SceneManager.h>
#include <Scene.h>
#include <GameObject.h>

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
    else if (mButtonPressed) {
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

    std::vector<Color> colorGradient = {
        Color(255, 0, 0, 255),   // Red
        Color(255, 255, 0, 255), // Yellow
        Color(0, 255, 0, 255),   // Green
        Color(0, 0, 255, 255)    // Blue
    };

    ParticleEmitter* fireworksEmitter = new ParticleEmitter(
        EmitterMode::Burst, // Emitter mode
        50.0f,             // Speed
        0.0f,               // Acceleration
        500,                // Min lifetime (ms)
        1000,               // Max lifetime (ms)
        Vector2(5, 5),      // Initial size
        Vector2(1, 1),      // End size
        0.0f,               // Initial rotation
        0.0f,               // Angular velocity
        0.0f,               // Angular acceleration
        colorGradient       // Color gradient
    );

    fireworksEmitter->setParticlesPerSecond(100);
    fireworksEmitter->setAngle(0, 360);
    fireworksEmitter->setLayer(4);

    Transform transform = mGameObject->getTransform();
    transform.position.y += 50;
    std::cout << "Emitter position: (" << transform.position.x << ", " << transform.position.y << ")" << std::endl;

    fireworksEmitter->setRelativeTransform(transform);

    // Add the emitter to the button's GameObject
    mGameObject->addComponent(fireworksEmitter);

    // Trigger the burst
    fireworksEmitter->burst(300);

    std::cout << "Emitter active: " << fireworksEmitter->isActive() << std::endl;
}