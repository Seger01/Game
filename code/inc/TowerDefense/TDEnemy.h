#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject/GameObject.h"
#include <vector>

struct Waypoint {
    float x;
    float y;
};

class TDEnemy : public IBehaviourScript {
public:
    TDEnemy(float health, float speed, int reward, const std::vector<Waypoint>& path);
    
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<TDEnemy>(*this); 
    }
    
    void takeDamage(float damage);
    bool isDead() const { return mHealth <= 0; }
    bool hasReachedEnd() const { return mReachedEnd; }
    int getReward() const { return mReward; }
    
private:
    void moveAlongPath();
    void die();
    
    float mHealth;
    float mMaxHealth;
    float mSpeed;
    int mReward;
    std::vector<Waypoint> mPath;
    size_t mCurrentWaypointIndex;
    bool mReachedEnd;
};
