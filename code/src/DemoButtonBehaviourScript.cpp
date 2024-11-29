#include "DemoButtonBehaviourScript.h"

#include "DemoInitBehaviourScript.h"
#include "EngineBravo.h"
#include "GameObject.h"
#include "LevelManagerBehaviourScript.h"

SpriteDef guySpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{182, 389, 20, 27}, 20, 27};

DemoButtonBehaviourScript::DemoButtonBehaviourScript() {}

DemoButtonBehaviourScript::~DemoButtonBehaviourScript() {}

void DemoButtonBehaviourScript::onStart() {}

void DemoButtonBehaviourScript::onUpdate() {
    std::cout << "Button Position: " << mGameObject->getTransform().position.x << ", "
              << mGameObject->getTransform().position.y << std::endl;
}

void DemoButtonBehaviourScript::onCollide(GameObject* aGameObject) {
    if (aGameObject != nullptr) {
        if (aGameObject->getTag() == "Player") {
            static bool buttonPressed = false;
            if (buttonPressed) {
                return;
            }
            GameObject* guy = new GameObject;

            Transform transform;
            transform.position.x = mGameObject->getTransform().position.x;
            transform.position.y = mGameObject->getTransform().position.y;
            guy->setTransform(transform);

            Sprite* guySprite = EngineBravo::getInstance().getResourceManager().createSprite(guySpriteDef);
            guySprite->setLayer(3);
            guy->addComponent(guySprite);

            guy->setTag("Guy");
            EngineBravo::getInstance().getSceneManager().getCurrentScene()->addGameObject(guy);
            buttonPressed = true;

            for (Component* component : mGameObject->getComponents<Sprite>()) {
                if (component->getTag() == "ButtonDownSprite") {
                    component->setActive(true);
                }
                if (component->getTag() == "ButtonUpSprite") {
                    component->setActive(false);
                }
            }
        }
    }
}
