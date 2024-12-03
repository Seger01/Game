#ifndef BUTTONBEHAVIOURSCRIPT_H
#define BUTTONBEHAVIOURSCRIPT_H

#include "IBehaviourScript.h"

class : public IBehaviourScript {
public:
    MainMenuBehaviourScript();
    ~MainMenuBehaviourScript();

    void onStart() override;
    void onUpdate() override;

    virtual std::unique_ptr<Component> clone() const override {
        return std::make_unique<MainMenuBehaviourScript>(*this);
    }

private:
    void onPlayRelease();
    void onMultiplayerRelease();
    void onDemoRelease();
    void onExitRelease();
};

#endif // MAINMENUBEHAVIOURSCRIPT_H
