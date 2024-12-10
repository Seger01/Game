#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <Pathfinding.h>
#include <SpriteDef.h>

class EnemyBehaviourScript : public IBehaviourScript {
public:
    EnemyBehaviourScript(float aHealth);
    EnemyBehaviourScript(const EnemyBehaviourScript& other);
    ~EnemyBehaviourScript() {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;

    std::unique_ptr<Component> clone() const override { return std::make_unique<EnemyBehaviourScript>(*this); }
    void deactivateAllAnimations();
    void setFlipX(bool aState);
    void setFlipY(bool aState);

    void moveWithPathfinding();
    void setPathfinding(std::unique_ptr<Pathfinding>&& aPathfinding);
    void setMapWidth(int aMapWidth);
    void setMapHeight(int aMapHeight);

    int getMapWidth() const;
    int getMapHeight() const;
    std::unique_ptr<Pathfinding> getPathfinding() const;
private: 
    void toggleAnimaionEnabled();
    void setAnimationActive(std::string aAnimationTag, bool aState);
    void takeDamage(float aDamage);
    void onDeath();
    bool isValidPosition(int position) const;
    float vectorLength(const Vector2& vec);
    Vector2 normalizeVector(const Vector2& vec);
    int getGridPosition(const Vector2& position) const;
    void visualizePath(const std::vector<int>& path);
    void visualizeGraph();
    void removePathVisualization();
    void removeGraphVisualization();

private :
    float mHealth;
    bool mIsDead;

    std::unique_ptr<Pathfinding> mPathfinding = nullptr;
    int mMapWidth;
    int mMapHeight;
    std::vector<int> mPath;
    size_t mCurrentPathIndex;
    float mPathUpdateTime;
    Vector2 mPreviousPlayerPosition;
    SpriteDef mPathMarkerSpriteDef;
    SpriteDef mGraphNodeSpriteDef;

    bool drawPath = false;
    bool drawGraph = false;

};