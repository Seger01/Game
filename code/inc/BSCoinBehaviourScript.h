#pragma once

#include <Components/IBehaviourScript.h>
#include <Components/Sprite.h>
#include <Engine/EngineBravo.h>
#include <GameObject.h>
#include <Global/FSConverter.h>

class BSCoinBehaviourScript : public IBehaviourScript
{
public:
	BSCoinBehaviourScript();
	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<BSCoinBehaviourScript>(*this); }
};
