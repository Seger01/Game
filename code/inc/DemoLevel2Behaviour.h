#pragma once

#include <GameObject.h>
#include <IBehaviourScript.h>
#include <Pathfinding.h>
#include <iostream>
#include <vector>

class DemoLevel2Behaviour : public IBehaviourScript {
public:
    DemoLevel2Behaviour(std::unique_ptr<Pathfinding>&& aPathfinding, int aMapWidth, int aMapHeight) 
        : mPathfinding(std::move(aPathfinding)), mMapWidth(aMapWidth), mMapHeight(aMapHeight), mMovingUp(true), mInitialY(0.0f), mCurrentPathIndex(0) {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<DemoLevel2Behaviour>(std::make_unique<Pathfinding>(*mPathfinding), mMapWidth, mMapHeight); 
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
    std::unique_ptr<Pathfinding> mPathfinding;
    int mMapWidth;
    int mMapHeight;
    std::vector<int> mPath;
    size_t mCurrentPathIndex;
};