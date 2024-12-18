#pragma once

#include <IBehaviourScript.h>

class BulletDestroyParticleBehaviourScript : public IBehaviourScript
{
public:
	void onStart() override;
	void onUpdate() override;

	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<BulletDestroyParticleBehaviourScript>(*this);
	}

private:
	double mElapsedTime;
};
