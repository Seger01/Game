#pragma once

#include <GameObject.h>
#include <Sprite.h>
#include <IBehaviourScript.h>


class ECCoinBehaviourScript : public IBehaviourScript {
public:
    ECCoinBehaviourScript();
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<ECCoinBehaviourScript>(*this); }
};
