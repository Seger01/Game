#pragma once

#include <IBehaviourScript.h>
#include <GameObject.h>
#include <iostream>
#include <SpriteDef.h>
#include <Sprite.h>

class DemoParticlesButtonBehaviourScript : public IBehaviourScript {
public:
    DemoParticlesButtonBehaviourScript();
    ~DemoParticlesButtonBehaviourScript() {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoParticlesButtonBehaviourScript>(*this); }

private:
    void updateButtonState();
    void launchParticles();
private:
    bool mButtonPressed;

};
