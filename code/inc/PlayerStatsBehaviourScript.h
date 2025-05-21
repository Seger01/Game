#pragma once

#include "Components/IBehaviourScript.h"
#include "PlayerBehaviourScript.h"
#include "Rect.h"
#include "UI/Text.h"

class PlayerStatsBehaviourScript : public IBehaviourScript
{
public:
	PlayerStatsBehaviourScript();

	std::unique_ptr<Component> clone() const override { return std::make_unique<PlayerStatsBehaviourScript>(*this); }

	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

private:
	// float mHealth;
	// float mMaxHealth;
	float mHealthBarWidth;
	Rect mFullHealthBarForegroundSourceRect;
	Text* mBSCountText;
};
