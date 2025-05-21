#pragma once

#include <Components/IBehaviourScript.h>
#include <Components/Sprite.h>
#include <GameObject.h>
#include <SpriteDef.h>
#include <iostream>

class DemoParticlesButtonBehaviourScript : public IBehaviourScript
{
public:
	DemoParticlesButtonBehaviourScript();

	~DemoParticlesButtonBehaviourScript() {}

	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<DemoParticlesButtonBehaviourScript>(*this);
	}

private:
	void updateButtonState();
	void launchParticles();
	void removeParticles();

private:
	bool mButtonPressed;
};
