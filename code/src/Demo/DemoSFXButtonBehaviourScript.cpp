#include "DemoSFXButtonBehaviourScript.h"
#include <AudioManager.h>
#include <AudioSource.h>
#include <EngineBravo.h>

DemoSFXButtonBehaviourScript::DemoSFXButtonBehaviourScript() {}

void DemoSFXButtonBehaviourScript::onStart() {}

void DemoSFXButtonBehaviourScript::onUpdate() { updateButtonState(); }

void DemoSFXButtonBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject == nullptr || aGameObject->getTag() != "Player")
		return;

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();
	AudioManager& audioManager = engine.getAudioManager();

	if (mGameObject->getTag() == "ButtonSFX")
	{
		if (audioManager.getFacade().isPlaying("Audio/gun1.wav"))
		{
			return;
		}
		else
		{
			playSFX();
		}
	}
}

void DemoSFXButtonBehaviourScript::updateButtonState()
{
	EngineBravo& engine = EngineBravo::getInstance();
	AudioManager& audioManager = engine.getAudioManager();
	Scene& scene = engine.getSceneManager().getCurrentScene();
	GameObject* button = mGameObject;

	if (audioManager.getFacade().isPlaying("Audio/gun1.wav"))
	{
		for (Component& component : button->getComponents<Sprite>())
		{
			if (component.getTag() == "ButtonDownSprite")
			{
				component.setActive(true);
			}
			else if (component.getTag() == "ButtonUpSprite")
			{
				component.setActive(false);
			}
		}
	}
	else
	{
		for (Component& component : button->getComponents<Sprite>())
		{
			if (component.getTag() == "ButtonDownSprite")
			{
				component.setActive(false);
			}
			else if (component.getTag() == "ButtonUpSprite")
			{
				component.setActive(true);
			}
		}
	}
}

void DemoSFXButtonBehaviourScript::playSFX()
{
	EngineBravo& engine = EngineBravo::getInstance();
	AudioManager& audioManager = engine.getAudioManager();

	std::string path = "Audio/gun1.wav";
	AudioSource audio(path, false);
	if (!audioManager.getFacade().audioIsLoaded(path))
	{
		audioManager.loadSound(audio);
	}

	audioManager.play(audio);
}
