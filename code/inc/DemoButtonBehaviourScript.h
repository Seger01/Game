#ifndef DEMOBUTTONBEHAVIOURSCRIPT_H
#define DEMOBUTTONBEHAVIOURSCRIPT_H

#include "Components/IBehaviourScript.h"

class GameObject;

class DemoButtonBehaviourScript : public IBehaviourScript
{
public:
	DemoButtonBehaviourScript();
	~DemoButtonBehaviourScript();

	void onStart() override;
	void onUpdate() override;

	void onCollide(GameObject* aGameObject) override;

	virtual std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<DemoButtonBehaviourScript>(*this);
	}

private:
};

#endif // DEMOBUTTONBEHAVIOURSCRIPT_H
