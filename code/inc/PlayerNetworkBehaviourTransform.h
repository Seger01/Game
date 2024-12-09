#ifndef PLAYERNETWORKBEHAVIOURTRANSFORM_H
#define PLAYERNETWORKBEHAVIOURTRANSFORM_H

#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Network/INetworkSerializable.h>
#include <Network/NetworkVariable.h>

class transformSerializable : public INetworkSerializable
{
public:
	transformSerializable()
	{
		mPosition = Vector2(0, 0);
		mRotation = 0;
	}

	transformSerializable(const transformSerializable& other)
	{
		mPosition = other.mPosition;
		mRotation = other.mRotation;
	}

	bool operator==(const transformSerializable& other) const
	{
		return mPosition.x == other.mPosition.x && mPosition.y == other.mPosition.y && mRotation == other.mRotation;
	}

	bool operator!=(const transformSerializable& other) const { return !(*this == other); }

	void serialize(SLNet::BitStream& stream) const override
	{
		stream.Write(mPosition.x);
		stream.Write(mPosition.y);
		stream.Write(mRotation);
	}

	void deserialize(SLNet::BitStream& stream) override
	{
		stream.Read(mPosition.x);
		stream.Read(mPosition.y);
		stream.Read(mRotation);
	}

	void setPosition(Vector2 position) { mPosition = position; }

	Vector2 getPosition() const { return mPosition; }

	void setRotation(float rotation) { mRotation = rotation; }

	float getRotation() const { return mRotation; }

private:
	Vector2 mPosition;
	float mRotation;
};

class PlayerNetworkBehaviourTransform : public INetworkBehaviour
{
public:
	PlayerNetworkBehaviourTransform();
	PlayerNetworkBehaviourTransform(const PlayerNetworkBehaviourTransform& other);

	// void onStart() override {}

	void onUpdate() override;

	// void onNetworkSpawn() override {}

	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<PlayerNetworkBehaviourTransform>(*this);
	}

private:
	NetworkVariable<transformSerializable> mTransformSerialize{this};
};

#endif