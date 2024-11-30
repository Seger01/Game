#include "Components/IButtonBehaviourScript.h"

#include <iostream>

#include "Components/Sprite.h"
#include "GameObject.h"

class MainMenuButtonBehaviour : public IButtonBehaviourScript {
public:
    MainMenuButtonBehaviour() {}
    ~MainMenuButtonBehaviour() {}

    std::unique_ptr<Component> clone() const override { return std::make_unique<MainMenuButtonBehaviour>(*this); }

    void onButtonPressed() override {}

    void onButtonReleased() override {}

    void onButtonHover() override {
        for (auto& sprite : mGameObject->getComponents<Sprite>()) {
            sprite->setColorFilter({255, 255, 255, 255});
        }
    }

    void onButtonUnhover() override {
        for (auto& sprite : mGameObject->getComponents<Sprite>()) {
            sprite->setColorFilter({255, 255, 255, 100});
        }
    }
};
