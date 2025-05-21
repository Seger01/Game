#include "DemoMusicButtonBehaviourScript.h"
#include <Audio/AudioManager.h>
#include <Components/Sprite.h>
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <Scene.h>

DemoMusicButtonBehaviourScript::DemoMusicButtonBehaviourScript() : mPlayButtonPressed(false), mResetButtonPressed(false)
{
}

void DemoMusicButtonBehaviourScript::onStart() {}

void DemoMusicButtonBehaviourScript::onUpdate() {}

void DemoMusicButtonBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject == nullptr || aGameObject->getTag() != "Player")
		return;

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();

	// Handle Start/Stop button
	if (mGameObject->getTag() == "ButtonStartStopMusic")
	{
		togglePlayStop(&scene);
	}
	// Handle Reset button
	else if (mGameObject->getTag() == "ButtonResetMusic")
	{
		resetAll(&scene);
	}
}

// Toggle Play/Stop state and control music
void DemoMusicButtonBehaviourScript::togglePlayStop(Scene* scene)
{
	if (!mPlayButtonPressed)
	{
		playMusic();
		setButtonState(mGameObject, true);
	}
	else
	{
		pauseMusic();
		setButtonState(mGameObject, false);
	}
	mPlayButtonPressed = !mPlayButtonPressed;

	// Reset Reset button to default state when Play is pressed
	if (mPlayButtonPressed)
	{
		GameObject* resetButton = getButton(scene, "ButtonResetMusic");
		if (resetButton)
			setButtonState(resetButton, false);
		mResetButtonPressed = false;
	}
}

// Reset all states and stop music
void DemoMusicButtonBehaviourScript::resetAll(Scene* scene)
{
	// Set Reset button to "down" state
	GameObject* resetButton = getButton(scene, "ButtonResetMusic");
	if (resetButton)
	{
		setButtonState(resetButton, true);
	}

	// Stop the music and reset Start/Stop button to default state
	stopMusic();
	GameObject* playButton = getButton(scene, "ButtonStartStopMusic");
	if (playButton)
	{
		setButtonState(playButton, false);
	}

	mPlayButtonPressed = false;
	mResetButtonPressed = true;
}

void DemoMusicButtonBehaviourScript::playMusic()
{
	EngineBravo& engine = EngineBravo::getInstance();
	AudioManager& audioManager = engine.getAudioManager();

	std::string path = "Audio/music.wav";
	AudioSource audio(path, true);
	audio.setVolume(100);
	if (!audioManager.getFacade().audioIsLoaded(path))
	{
		audioManager.loadSound(audio);
	}

	audioManager.resume(audio);
}

void DemoMusicButtonBehaviourScript::pauseMusic()
{
	EngineBravo& engine = EngineBravo::getInstance();
	AudioManager& audioManager = engine.getAudioManager();
	// audioManager.getFacade().stopMusic();
	//	audioManager.getFacade().stopMusic();
	std::string path = "Audio/music.wav";
	AudioSource audio(path, true);
	audio.setVolume(100);
	audioManager.pause(audio);
}

void DemoMusicButtonBehaviourScript::stopMusic()
{
	EngineBravo& engine = EngineBravo::getInstance();
	AudioManager& audioManager = engine.getAudioManager();
	// audioManager.getFacade().stopMusic();
	//	audioManager.getFacade().stopMusic();
	std::string path = "Audio/music.wav";
	AudioSource audio(path, true);
	audio.setVolume(100);
	audioManager.stop(audio);
}

// Set button visual state
void DemoMusicButtonBehaviourScript::setButtonState(GameObject* button, bool isDown)
{
	for (Component& component : button->getComponents<Sprite>())
	{
		if (component.getTag() == "ButtonDownSprite")
		{
			component.setActive(isDown);
		}
		else if (component.getTag() == "ButtonUpSprite")
		{
			component.setActive(!isDown);
		}
	}
}

// Fetch a button by tag
GameObject* DemoMusicButtonBehaviourScript::getButton(Scene* scene, const std::string& tag)
{
	auto buttons = scene->getGameObjectsWithTag(tag);
	return !buttons.empty() ? &buttons[0].get() : nullptr;
}
