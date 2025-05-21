#ifndef PLAYERBEHAVIOURSCRIPT_H
#define PLAYERBEHAVIOURSCRIPT_H

#include <Animation.h>
#include <GameObject.h>
#include <Network/INetworkBehaviour.h>
#include <Point.h>

class PlayerBehaviourScript : public INetworkBehaviour
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<PlayerBehaviourScript>(*this); }

	float getHealth();
	void setHealth(float aHealth);
	float getMaxHealth();
	void setMaxHealth(float aMaxHealth);
	int getECCount();
	void setECCount(int aECCount);
	int getBSCount();
	void setBSCount(int aBSCount);

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
	void handleAspectRatioTest();
	void fireBullet(Point mousePosition);

private:
	int mECCount;
	int mBSCount;
	float mHealth;
	float mMaxHealth;
};

#endif
