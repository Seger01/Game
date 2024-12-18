#pragma once
#include <IBehaviourScript.h>

class NetworkDemoSceneBehaviour : public IBehaviourScript
{
public:
	NetworkDemoSceneBehaviour();
	NetworkDemoSceneBehaviour(const NetworkDemoSceneBehaviour& other);

	std::unique_ptr<Component> clone() const override { return std::make_unique<NetworkDemoSceneBehaviour>(*this); }

	void onUpdate() override;
};