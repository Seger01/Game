#include "AudioBehaviourScript.h"

#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <Input/Input.h>

void AudioBehaviourScript::onStart() {}

void AudioBehaviourScript::onUpdate()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	Input& input = Input::getInstance();
	if (input.GetKeyDown(Key::Key_P))
	{
		mGameObject->getComponentsWithTag<AudioSource>("gun")[0].get().play();
	}

	AudioManager& audioManager = EngineBravo::getInstance().getAudioManager();
	AudioSource& step = mGameObject->getComponentsWithTag<AudioSource>("step")[0];
	if ((input.GetKey(Key::Key_W) || input.GetKey(Key::Key_A) || input.GetKey(Key::Key_S) ||
		 input.GetKey(Key::Key_D)) &&
		!audioManager.getFacade().isPlaying(step.getFileName()))
	{

		step.play();
	}
}

std::unique_ptr<Component> AudioBehaviourScript::clone() const { return std::make_unique<AudioBehaviourScript>(*this); }
