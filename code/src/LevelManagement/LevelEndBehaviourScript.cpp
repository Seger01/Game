#include "LevelEndBehaviourScript.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Scene.h>
#include <iostream>

void LevelEndBehaviourScript::onStart()
{
	auto& sceneManager = EngineBravo::getInstance().getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();
	auto levelManagerObjects = scene.getGameObjectsWithTag("LevelManager");

	if (!levelManagerObjects.empty())
	{
		auto levelManagerComponents = levelManagerObjects[0].get().getComponents<LevelManagerBehaviourScript>();
		if (!levelManagerComponents.empty())
		{
			mLevelManager = &levelManagerComponents[0].get();
		}
		else
		{
			std::cerr << "LevelManagerBehaviourScript component not found in "
						 "LevelEndBehaviourScript::onStart\n";
		}
	}
	else
	{
		std::cerr << "LevelManager GameObject not found in "
					 "LevelEndBehaviourScript::onStart\n";
	}

	if (mLevelManager == nullptr)
	{
		std::cerr << "LevelManager not found in LevelEndBehaviourScript::onStart\n";
	}
}

void LevelEndBehaviourScript::onUpdate() {}

void LevelEndBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject != nullptr)
	{

		if (aGameObject->getTag() == "Player")
		{
			mLevelManager->doneWithCurrentLevel();
		}
	}
	else
	{
		std::cerr << "GameObject is null in LevelEndBehaviourScript::onCollide\n";
	}
}
