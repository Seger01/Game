#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject.h"
#include <iostream>
#include <SpriteDef.h>


class DemoPhysicsButtonBehaviourScript : public IBehaviourScript {
public:
    DemoPhysicsButtonBehaviourScript();
    ~DemoPhysicsButtonBehaviourScript() {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoPhysicsButtonBehaviourScript>(*this); }

private:
    void updateButtonState();
    void spawnBox();
    void spawnCircle();
    void removeBox();
    void removeCircle();

private:
    SpriteDef mBoxSpriteDef;
    SpriteDef mCircleSpriteDef;
    bool mButtonPressed;
};
