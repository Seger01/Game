#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject.h"
#include <iostream>
#include <SpriteDef.h>
#include <Vector2.h>


class DemoPhysicsButtonBehaviourScript : public IBehaviourScript {
public:
    DemoPhysicsButtonBehaviourScript();
    ~DemoPhysicsButtonBehaviourScript() {}
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoPhysicsButtonBehaviourScript>(*this); }

private:
    void updateButtonState(const std::string& buttonTag);
    void updateButtonSprites(bool isActive);
    void spawnBox(const Vector2& aPosition, const std::string& aName, const Vector2& aForce);
    void spawnCircle(const Vector2& aPosition, const std::string& aName);
    void removeBox(const std::string& aName);
    void removeCircle(const std::string& aName);
    void toggleGravity();

private:
    SpriteDef mBoxSpriteDef;
    SpriteDef mCircleSpriteDef;
    bool mButtonPressedBox;
    bool mButtonPressedCircle;
    bool mButtonPressedGravity;
    bool mButtonPressedFilter;
    bool mBoxGravitySpawned;
};
