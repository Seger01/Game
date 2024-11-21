#ifndef LEVELMANAGERBEHAVIOURSCRIPT_H
#define LEVELMANAGERBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>

class LevelManagerBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<LevelManagerBehaviourScript>(*this); }


private:
    void doneWithCurrentLevel();
    void createLevelCreator();

private:
    int mCurrentLevel;
};

#endif