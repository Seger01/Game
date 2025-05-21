#ifndef MAINMENUBEHAVIOURSCRIPT_H
#define MAINMENUBEHAVIOURSCRIPT_H

#include "Components/IBehaviourScript.h"

class MainMenuBehaviourScript : public IBehaviourScript
{
public:
	MainMenuBehaviourScript();
	~MainMenuBehaviourScript();

	void onStart() override;
	void onUpdate() override;

	virtual std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<MainMenuBehaviourScript>(*this);
	}

private:
	void onPlayRelease();
	void onMultiplayerRelease();
	void onDemoRelease();
	void onExitRelease();
	void onDemoMultiRelease();
};

#endif // MAINMENUBEHAVIOURSCRIPT_H
