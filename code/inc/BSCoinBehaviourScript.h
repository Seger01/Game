#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <FSConverter.h>
#include <EngineBravo.h>
#include <IBehaviourScript.h>

class BSCoinBehaviourScript : public IBehaviourScript {
public:
    BSCoinBehaviourScript();
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<BSCoinBehaviourScript>(*this); }
};