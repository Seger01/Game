#ifndef LEVELENDBEHAVIOURSCRIPT_H
#define LEVELENDBEHAVIOURSCRIPT_H

#include "LevelManagerBehaviourScript.h"
#include <Components/IBehaviourScript.h>
#include <GameObject.h>

class LevelEndBehaviourScript : public IBehaviourScript {
public:
  void onStart() override;
  void onUpdate() override;
  void onCollide(GameObject *aGameObject) override;

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<LevelEndBehaviourScript>(*this);
  }

private:
  LevelManagerBehaviourScript *mLevelManager;
};

#endif