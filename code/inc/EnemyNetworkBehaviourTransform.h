#ifndef ENEMYNETWORKBEHAVIOURTRANSFORM_H
#define ENEMYNETWORKBEHAVIOURTRANSFORM_H

#include "PlayerNetworkBehaviourTransform.h"
#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Network/INetworkSerializable.h>
#include <Network/NetworkVariable.h>

class EnemyNetworkBehaviourTransform : public INetworkBehaviour
{
public:
	EnemyNetworkBehaviourTransform();
	EnemyNetworkBehaviourTransform(const EnemyNetworkBehaviourTransform& other);

	// void onStart() override {}

	void onUpdate() override;

	// void onNetworkSpawn() override {}

	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<EnemyNetworkBehaviourTransform>(*this);
	}

private:
	NetworkVariable<transformSerializable> mTransformSerialize;
};

#endif