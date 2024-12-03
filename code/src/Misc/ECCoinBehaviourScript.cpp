#include "ECCoinBehaviourScript.h"

ECCoinBehaviourScript::ECCoinBehaviourScript() {
}

void ECCoinBehaviourScript::onStart() {
}

void ECCoinBehaviourScript::onUpdate() {
}

void ECCoinBehaviourScript::onCollide(GameObject* aGameObject) {
    if (aGameObject != nullptr) {
        if (aGameObject->getTag() == "Player") {
            // Add score
            // Play sound
            // Destroy coin
        }
    }
}