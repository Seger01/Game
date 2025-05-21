#pragma once

#include <Components/IBehaviourScript.h>
#include <Components/Sprite.h>
#include <GameObject.h>

class ECCoinBehaviourScript : public IBehaviourScript
{
public:
	ECCoinBehaviourScript();
	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<ECCoinBehaviourScript>(*this); }
};
