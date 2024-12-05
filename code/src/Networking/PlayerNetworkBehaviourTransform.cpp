#include "PlayerNetworkBehaviourTransform.h"

// Register the type
REGISTER_NETWORK_SERIALIZABLE(transformSerializable);

PlayerNetworkBehaviourTransform::PlayerNetworkBehaviourTransform()
	: INetworkBehaviour("PlayerNetworkBehaviourTransform")
{
}

PlayerNetworkBehaviourTransform::PlayerNetworkBehaviourTransform(const PlayerNetworkBehaviourTransform& other)
	: INetworkBehaviour(other)
{
	mNetworkVariables.clear();
	mNetworkVariables.push_back(mTransformSerialize);
}

void PlayerNetworkBehaviourTransform::onUpdate()
{
	if (isOwner())
	{
		mTransformSerialize.getValue().setPosition(mGameObject->getTransform().position); // Set the network variable
	}
	else
	{
		Transform transform(mTransformSerialize.getValue().getPosition());
		mGameObject->setTransform(transform); // Read the network variable
	}
}