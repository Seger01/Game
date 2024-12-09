#pragma once

#include <GameObject.h>
#include <IBehaviourScript.h>
#include <Pathfinding.h>
#include <iostream>
#include <vector>

class DemoLevel2Behaviour : public IBehaviourScript {
public:
    //DemoLevel2Behaviour(std::unique_ptr<Pathfinding>&& aPathfinding, int aMapWidth, int aMapHeight) 
    //    : mPathfinding(std::move(aPathfinding)), mMapWidth(aMapWidth), mMapHeight(aMapHeight), mMovingUp(true), mInitialY(0.0f), mCurrentPathIndex(0) {}
    DemoLevel2Behaviour() : mMovingUp(true), mInitialY(0.0f) {};
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<DemoLevel2Behaviour>(*this); 
    }

private:
    void moveEnemy();
    void scaleEnemy();
    void rotateEnemy();
    void moveWithPathfinding();
    int getGridPosition(const Vector2& position) const;
    bool isValidPosition(int position) const;


private:
    bool mMovingUp;
    float mInitialY;
};