#ifndef DEMOINITBEHAVIOURSCRIPT_H
#define DEMOINITBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>

class DemoInitBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;

    void createFirstLevel();

    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoInitBehaviourScript>(*this); }

private:
};

#endif
