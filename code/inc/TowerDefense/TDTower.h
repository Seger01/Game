#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject/GameObject.h"

enum class TowerType {
    BASIC,
    RAPID,
    SNIPER,
    SPLASH
};

class TDTower : public IBehaviourScript {
public:
    TDTower(TowerType type);
    
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override {}
    
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<TDTower>(*this); 
    }
    
    int getCost() const { return mCost; }
    TowerType getType() const { return mType; }
    
private:
    void findAndShootTarget();
    GameObject* findNearestEnemy();
    void shootAt(GameObject* target);
    
    TowerType mType;
    float mRange;
    float mDamage;
    float mFireRate;
    float mTimeSinceLastShot;
    int mCost;
};
