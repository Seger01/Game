#pragma once

#include <GameObject.h>
#include <IBehaviourScript.h>

class DemoSFXButtonBehaviourScript : public IBehaviourScript {
public:
    DemoSFXButtonBehaviourScript();
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoSFXButtonBehaviourScript>(*this); }

private:
    void playSFX();
    void updateButtonState();
    bool mSFXButtonPressed = false;
};