#include "PlayerNetworkBehaviourTransform.h"
#include "Components/RigidBody.h"
#include "Global/Time.h"

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
	if (isServer())
	{
		mTransformSerialize.getValue().setPosition(mGameObject->getTransform().position); // Set the network variable
		mTransformSerialize.getValue().setRotation(mGameObject->getTransform().rotation); // Set the network variable
	}
	else
	{
		// Client-side prediction
		Transform predictedTransform(mGameObject->getTransform());
		predictedTransform.position +=
			mGameObject->getComponents<RigidBody>()[0].get().getLinearVelocity() * Time::deltaTime;
		mGameObject->setTransform(predictedTransform);

		// Interpolation
		Transform networkTransform(mTransformSerialize.getValue().getPosition());
		networkTransform.rotation = mTransformSerialize.getValue().getRotation();

		Transform localTransform(mGameObject->getTransform());

		Vector2 interpolatedPosition;
		interpolatedPosition.x = localTransform.position.x +
								 (networkTransform.position.x - localTransform.position.x) * INTERPOLATION_FACTOR;
		interpolatedPosition.y = localTransform.position.y +
								 (networkTransform.position.y - localTransform.position.y) * INTERPOLATION_FACTOR;

		Transform interpolatedTransform(interpolatedPosition);
		interpolatedTransform.rotation = networkTransform.rotation;

		// Reconciliation
		if (predictedTransform.position != networkTransform.position)
		{
			mGameObject->setTransform(interpolatedTransform);
		}
	}
}
