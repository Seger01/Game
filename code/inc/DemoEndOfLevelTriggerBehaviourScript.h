#ifndef DEMOENDOFLEVELBEHAVIOUR_H
#define DEMOENDOFLEVELBEHAVIOUR_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>

class DemoEndOfLevelTriggerBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;

    std::unique_ptr<Component> clone() const override {
        return std::make_unique<DemoEndOfLevelTriggerBehaviourScript>(*this);
    }

private:
};

#endif
