#pragma once

#include <GameObject.h>
#include <IBehaviourScript.h>

class DemoLevel2Behaviour : public IBehaviourScript {
public:
    DemoLevel2Behaviour();
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoLevel2Behaviour>(*this); }

private:
    void moveEnemy();
    void scaleEnemy();
    void rotateEnemy();

private:
    bool mMovingUp;
    float mInitialY;
};