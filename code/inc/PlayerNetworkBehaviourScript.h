#ifndef PLAYERNETWORKBEHAVIOURSCRIPT_H
#define PLAYERNETWORKBEHAVIOURSCRIPT_H

#include <Animation.h>
#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Point.h>

class PlayerNetworkBehaviourScript : public INetworkBehaviour
{
public:
	PlayerNetworkBehaviourScript() : INetworkBehaviour("PlayerNetworkBehaviourScript") {}

	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<PlayerNetworkBehaviourScript>(*this); }

private:
	std::string currentActiveAnimationTag();

	void setFlipX(bool aState);
	void setFlipY(bool aState);

	void toggleAnimaionEnabled();
	void setAnimationActive(std::string aAnimationTag, bool aState);
	void deactivateAllAnimations();

	void handleAnimations();
	void handleMovement();
	void hanldeCameraMovement();
	void fireBullet(Point mousePosition);
};

#endif