#ifndef DEMOMANAGERBEHAVIOURSCRIPT_H
#define DEMOMANAGERBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>

class DemoManagerBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;

    void createFirstScene();
    void createSecondScene();

    void nextScene();

    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoManagerBehaviourScript>(*this); }

private:
    int mCurrentScene;
};

#endif
