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
	// mGameObject->getComponents<RigidBody>()[0]->getForcesBuffer();
	// if (isOwner())
	// {
	// 	mForcesSerialize.getValue().setPosition(mGameObject->getTransform().position); // Set the network variable
	// 	mForcesSerialize.getValue().setRotation(mGameObject->getTransform().rotation); // Set the network variable
	// }
	// else
	// {
	// 	Transform transform(mForcesSerialize.getValue().getPosition());
	// 	transform.rotation = mForcesSerialize.getValue().getRotation();
	// 	mGameObject->setTransform(transform); // Read the network variable
	// }
}
