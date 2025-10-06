#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject/GameObject.h"
#include "Structs/Vector2.h"

class TDProjectile : public IBehaviourScript {
public:
    TDProjectile(GameObject* target, float damage, float speed);
    
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<TDProjectile>(*this); 
    }
    
private:
    GameObject* mTarget;
    float mDamage;
    float mSpeed;
    float mLifetime;
};
