#include "EnemyNetworkBehaviourForces.h"
#include "RigidBody.h"

// Register the type
REGISTER_NETWORK_SERIALIZABLE(forcesSerializable);

EnemyNetworkBehaviourForces::EnemyNetworkBehaviourForces()
	: mForcesSerialize{this}, INetworkBehaviour("EnemyNetworkBehaviourForces")
{
}

EnemyNetworkBehaviourForces::EnemyNetworkBehaviourForces(const EnemyNetworkBehaviourForces& other)
	: INetworkBehaviour(other), mForcesSerialize{this}
{
}

void EnemyNetworkBehaviourForces::onUpdate()
{
	std::vector<Vector2> forces = mGameObject->getComponents<RigidBody>()[0]->getForcesBuffer();

	if (isOwner())
	{
		mForcesSerialize.getValue().setForces(forces); // Set the network variable
	}
	else
	{
		for (const auto& force : mForcesSerialize.getValue().getForces())
		{
			mGameObject->getComponents<RigidBody>()[0]->addForce(force); // Read the network variable
		}
	}
}