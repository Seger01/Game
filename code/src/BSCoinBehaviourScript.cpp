#include "BSCoinBehaviourScript.h"

BSCoinBehaviourScript::BSCoinBehaviourScript() {
}

void BSCoinBehaviourScript::onStart() {
}

void BSCoinBehaviourScript::onUpdate() {
}

void BSCoinBehaviourScript::onCollide(GameObject* aGameObject) {
    if (aGameObject != nullptr) {
        if (aGameObject->getTag() == "Player") {
            // Add score
            // Play sound
            // Destroy coin
        }
    }
}

