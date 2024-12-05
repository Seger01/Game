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
		std::cout << "Constructor of transformSerializable" << std::endl;
	}

	transformSerializable(const transformSerializable& other)
	{
		mPosition = other.mPosition;
		std::cout << "Copy constructor of transformSerializable" << std::endl;
	}

	bool operator==(const transformSerializable& other) const
	{
		return mPosition.x == other.mPosition.x && mPosition.y == other.mPosition.y;
	}

	bool operator!=(const transformSerializable& other) const { return !(*this == other); }

	void serialize(SLNet::BitStream& stream) const override
	{
		stream.Write(mPosition.x);
		stream.Write(mPosition.y);
		// std::cout << "pointer of playerNetworkBehaviourTransform within the serialize " << this << std::endl;
	}

	void deserialize(SLNet::BitStream& stream) override
	{
		stream.Read(mPosition.x);
		stream.Read(mPosition.y);
	}

	void setPosition(Vector2 position)
	{
		mPosition = position;
		// std::cout << "pointer of playerNetworkBehaviourTransform within the setter " << this << std::endl;
	}

	Vector2 getPosition() const { return mPosition; }

private:
	Vector2 mPosition;
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