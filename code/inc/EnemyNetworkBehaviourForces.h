#ifndef ENEMYNETWORKBEHAVIOURTRANSFORM_H
#define ENEMYNETWORKBEHAVIOURTRANSFORM_H

#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Network/INetworkSerializable.h>
#include <Network/NetworkVariable.h>

class forcesSerializable : public INetworkSerializable
{
public:
	void serialize(SLNet::BitStream& stream) const override
	{
		for (const auto& force : mForces)
		{
			stream.Write(force.x);
			stream.Write(force.y);
		}
	}

	void deserialize(SLNet::BitStream& stream) override
	{
		for (auto& force : mForces)
		{
			stream.Read(force.x);
			stream.Read(force.y);
		}
	}

	void setForces(std::vector<Vector2> forces) { mForces = forces; }

	std::vector<Vector2> getForces() const { return mForces; }

private:
	std::vector<Vector2> mForces;
};

class EnemyNetworkBehaviourForces : public INetworkBehaviour
{
public:
	EnemyNetworkBehaviourForces();
	EnemyNetworkBehaviourForces(const EnemyNetworkBehaviourForces& other);

	// void onStart() override {}

	void onUpdate() override;

	// void onNetworkSpawn() override {}

	std::unique_ptr<Component> clone() const override { return std::make_unique<EnemyNetworkBehaviourForces>(*this); }

private:
	NetworkVariable<forcesSerializable> mForcesSerialize;
};

#endif