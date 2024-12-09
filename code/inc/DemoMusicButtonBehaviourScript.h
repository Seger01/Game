#pragma once

#include <GameObject.h>
#include <IBehaviourScript.h>
#include <Scene.h>
#include <Sprite.h>
#include <iostream>

class DemoMusicButtonBehaviourScript : public IBehaviourScript
{
public:
	DemoMusicButtonBehaviourScript();
	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override
	{
		return std::make_unique<DemoMusicButtonBehaviourScript>(*this);
	}

private:
	bool mPlayButtonPressed = false;
	bool mResetButtonPressed = false;

private:
	void togglePlayStop(Scene* scene);
	void resetAll(Scene* scene);
	void playMusic();
	void pauseMusic();
	void stopMusic();
	void setButtonState(GameObject* button, bool state);
	GameObject* getButton(Scene* scene, const std::string& tag);
};