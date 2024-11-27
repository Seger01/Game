#pragma once

#include <EngineBravo.h>
#include <GameObject.h>
#include <IBehaviourScript.h>
#include <SceneManager.h>
#include <iostream>

class BulletBehaviourScript : public IBehaviourScript {
public:
  BulletBehaviourScript(float damage);
  ~BulletBehaviourScript() {}
  void onStart() override;
  void onUpdate() override;
  void onCollide(GameObject *aGameObject) override;
  std::unique_ptr<Component> clone() const override {
    return std::make_unique<BulletBehaviourScript>(*this);
  }
  float getDamage() const { return mDamage; }
private:
    float mDamage;
    bool mIsMarkedForRemoval;
};