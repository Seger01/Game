#include "DemoEndOfLevelTriggerBehaviourScript.h"
#include "DemoManagerBehaviourScript.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Scene.h>
#include <iostream>

void DemoEndOfLevelTriggerBehaviourScript::onStart() {}

void DemoEndOfLevelTriggerBehaviourScript::onUpdate() {}

void DemoEndOfLevelTriggerBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject != nullptr)
	{

		for (GameObject& object :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("DemoManager"))
		{
			if (object.hasComponent<DemoManagerBehaviourScript>())
			{
				if (mGameObject->getTag() == "startDemoTrigger")
				{
					object.getComponents<DemoManagerBehaviourScript>()[0].get().nextScene("1");
				}
				else if (mGameObject->getTag() == "EndOfLevelTriggerDemo")
				{
					object.getComponents<DemoManagerBehaviourScript>()[0].get().nextScene("2");
				}
				else if (mGameObject->getTag() == "EndOfLevelTriggerStressTest")
				{
					object.getComponents<DemoManagerBehaviourScript>()[0].get().nextScene("3");
				}
			}
		}
	}
}
