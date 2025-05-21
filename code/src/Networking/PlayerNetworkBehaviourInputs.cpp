#include "PlayerNetworkBehaviourInputs.h"
#include "Components/RigidBody.h"
#include "Global/Time.h"
#include "Input/Input.h"
#include "Input/InputStructs.h"

// Register the type
REGISTER_NETWORK_SERIALIZABLE(inputsSerializable);

PlayerNetworkBehaviourInputs::PlayerNetworkBehaviourInputs()
	: mInputsSerialize{this}, INetworkBehaviour("PlayerNetworkBehaviourInputs")
{
}

PlayerNetworkBehaviourInputs::PlayerNetworkBehaviourInputs(const PlayerNetworkBehaviourInputs& other)
	: INetworkBehaviour(other), mInputsSerialize{this}
{
}

void PlayerNetworkBehaviourInputs::onUpdate()
{
	static const float movementSpeed = 160000.0f;

	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;

	Input& input = Input::getInstance();

	if (isOwner())
	{
		// Read the local values
		w = input.GetKey(Key::Key_W);
		a = input.GetKey(Key::Key_A);
		s = input.GetKey(Key::Key_S);
		d = input.GetKey(Key::Key_D);
		// Set the network variable
		mInputsSerialize.getValue().setButtons(w, a, s, d);

		// Client-side prediction
		Vector2 predictedPosition = mGameObject->getTransform().position;
		if (w)
			predictedPosition.y -= movementSpeed * Time::deltaTime;
		if (a)
			predictedPosition.x -= movementSpeed * Time::deltaTime;
		if (s)
			predictedPosition.y += movementSpeed * Time::deltaTime;
		if (d)
			predictedPosition.x += movementSpeed * Time::deltaTime;
		mGameObject->getTransform().position = predictedPosition;
	}
	else
	{
		// Read the network variable
		w = mInputsSerialize.getValue().getW();
		a = mInputsSerialize.getValue().getA();
		s = mInputsSerialize.getValue().getS();
		d = mInputsSerialize.getValue().getD();
		// Set the locals
		if (w)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(0, -movementSpeed * Time::deltaTime));
		}
		if (a)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(-movementSpeed * Time::deltaTime, 0));
		}
		if (s)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(0, movementSpeed * Time::deltaTime));
		}
		if (d)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(movementSpeed * Time::deltaTime, 0));
		}

		// Reconciliation
		Vector2 networkPosition = mGameObject->getTransform().position;
		if (w)
			networkPosition.y -= movementSpeed * Time::deltaTime;
		if (a)
			networkPosition.x -= movementSpeed * Time::deltaTime;
		if (s)
			networkPosition.y += movementSpeed * Time::deltaTime;
		if (d)
			networkPosition.x += movementSpeed * Time::deltaTime;

		if (mGameObject->getTransform().position != networkPosition)
		{
			mGameObject->getTransform().position = networkPosition;
		}
	}
}
