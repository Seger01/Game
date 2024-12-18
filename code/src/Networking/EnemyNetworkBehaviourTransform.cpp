#include "EnemyNetworkBehaviourTransform.h"

// Register the type
REGISTER_NETWORK_SERIALIZABLE(transformSerializable);

EnemyNetworkBehaviourTransform::EnemyNetworkBehaviourTransform()
	: mTransformSerialize{this}, INetworkBehaviour("EnemyNetworkBehaviourTransform")
{
}

EnemyNetworkBehaviourTransform::EnemyNetworkBehaviourTransform(const EnemyNetworkBehaviourTransform& other)
	: INetworkBehaviour(other), mTransformSerialize{this}
{
}

void EnemyNetworkBehaviourTransform::onUpdate()
{
	if (isOwner())
	{
		mTransformSerialize.getValue().setPosition(mGameObject->getTransform().position); // Set the network variable
		mTransformSerialize.getValue().setRotation(mGameObject->getTransform().rotation); // Set the network variable
	}
	else
	{
		Transform transform(mTransformSerialize.getValue().getPosition());
		transform.rotation = mTransformSerialize.getValue().getRotation();
		mGameObject->setTransform(transform); // Read the network variable
	}
}
