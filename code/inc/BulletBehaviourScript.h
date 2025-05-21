#pragma once

#include <Components/IBehaviourScript.h>
#include <Components/ParticleEmitter.h>
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <iostream>

class BulletBehaviourScript : public IBehaviourScript
{
public:
	BulletBehaviourScript(float damage);

	~BulletBehaviourScript() {}

	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<BulletBehaviourScript>(*this); }

	float getDamage() const { return mDamage; }

private:
	float mDamage;
	bool mIsMarkedForRemoval;
	GameObject* mParticleObject;
};
