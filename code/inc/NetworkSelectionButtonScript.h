#ifndef NETWORKBUTTONSCRIPT_H
#define NETWORKBUTTONSCRIPT_H

#include "Components/IButtonBehaviourScript.h"

#include "Text.h"

class ConnectButtonScript : public IButtonBehaviourScript
{
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