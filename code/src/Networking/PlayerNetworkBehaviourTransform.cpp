#include "PlayerNetworkBehaviourTransform.h"

// Register the type
REGISTER_NETWORK_SERIALIZABLE(transformSerializable);

PlayerNetworkBehaviourTransform::PlayerNetworkBehaviourTransform()
	: mTransformSerialize{this}, INetworkBehaviour("PlayerNetworkBehaviourTransform")
{
}

PlayerNetworkBehaviourTransform::PlayerNetworkBehaviourTransform(const PlayerNetworkBehaviourTransform& other)
	: INetworkBehaviour(other), mTransformSerialize{this}
{
}

void PlayerNetworkBehaviourTransform::onUpdate()
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