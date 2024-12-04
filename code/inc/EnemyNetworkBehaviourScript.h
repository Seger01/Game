#pragma once

#include "Network/INetworkBehaviour.h"
#include "GameObject.h"
#include <iostream>

class EnemyNetworkBehaviourScript : public INetworkBehaviour
{
public:
    EnemyNetworkBehaviourScript(float aHealth);
    ~EnemyNetworkBehaviourScript() {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;

    std::unique_ptr<Component> clone() const override { return std::make_unique<EnemyNetworkBehaviourScript>(*this); }
    void deactivateAllAnimations();
    void setFlipX(bool aState);
    void setFlipY(bool aState);
private: 
    void toggleAnimaionEnabled();
    void setAnimationActive(std::string aAnimationTag, bool aState);
    void takeDamage(float aDamage);
    void onDeath();
private :
    float mHealth;
    bool mIsDead;
};