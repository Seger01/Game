#ifndef PLAYERNETWORKBEHAVIOURFORCES_H
#define PLAYERNETWORKBEHAVIOURFORCES_H

#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Network/INetworkSerializable.h>
#include <Network/NetworkVariable.h>

class inputsSerializable : public INetworkSerializable
{
public:
	void serialize(SLNet::BitStream& stream) const override
	{
		stream.Write(wPressed);
		stream.Write(aPressed);
		stream.Write(sPressed);
		stream.Write(dPressed);
	}

	void deserialize(SLNet::BitStream& stream) override
	{
		stream.Read(wPressed);
		stream.Read(aPressed);
		stream.Read(sPressed);
		stream.Read(dPressed);
	}

	void setButtons(bool w, bool a, bool s, bool d)
	{
		wPressed = w;
		aPressed = a;
		sPressed = s;
		dPressed = d;
	}

	bool getW() const { return wPressed; }

	bool getA() const { return aPressed; }

	bool getS() const { return sPressed; }

	bool getD() const { return dPressed; }

private:
	bool wPressed{false};
	bool aPressed{false};
	bool sPressed{false};
	bool dPressed{false};
};

class PlayerNetworkBehaviourInputs : public INetworkBehaviour
{
public:
	PlayerNetworkBehaviourInputs();
	PlayerNetworkBehaviourInputs(const PlayerNetworkBehaviourInputs& other);

	// void onStart() override {}

	void onUpdate() override;

	// void onNetworkSpawn() override {}

	std::unique_ptr<Component> clone() const override { return std::make_unique<PlayerNetworkBehaviourInputs>(*this); }

private:
	NetworkVariable<inputsSerializable> mInputsSerialize;
};

#endif