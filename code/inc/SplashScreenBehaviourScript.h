#ifndef SPLASH_SCREEN_BEHAVIOUR_SCRIPT_H
#define SPLASH_SCREEN_BEHAVIOUR_SCRIPT_H

#include <Components/IBehaviourScript.h>
#include <chrono>

class SplashScreenBehaviourScript : public IBehaviourScript
{
public:
	SplashScreenBehaviourScript();
	virtual ~SplashScreenBehaviourScript() = default;

	void onStart() override;
	void onUpdate() override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<SplashScreenBehaviourScript>(*this); }

private:
	std::chrono::time_point<std::chrono::system_clock> startTime;
	GameObject& splashScreenPrefab;
};

#endif // SPLASH_SCREEN_BEHAVIOUR_SCRIPT_H
