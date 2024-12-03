#ifndef NETWORKBUTTONSCRIPT_H
#define NETWORKBUTTONSCRIPT_H

#include "Components/IButtonBehaviourScript.h"

#include "Text.h"

class NetworkSelectionButtonScript : public IButtonBehaviourScript {
public:
    NetworkSelectionButtonScript();
    ~NetworkSelectionButtonScript();

    std::unique_ptr<Component> clone() const override { return std::make_unique<NetworkSelectionButtonScript>(*this); }

    void onButtonPressed() override;

    void onButtonReleased() override;

private:
    void setButtonsVisibility();
};

class ConnectButtonScript : public IButtonBehaviourScript {
public:
    ConnectButtonScript(Text* aTextObject);
    ~ConnectButtonScript();

    std::unique_ptr<Component> clone() const override { return std::make_unique<ConnectButtonScript>(*this); }

    void onButtonPressed() override;

    void onButtonReleased() override;

private:
    Text* mTextObject{nullptr};
};

#endif // NETWORKBUTTONSCRIPT_H