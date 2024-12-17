#include "DemoEndOfLevelTriggerBehaviourScript.h"
#include "DemoManagerBehaviourScript.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <iostream>

void DemoEndOfLevelTriggerBehaviourScript::onStart() {}

void DemoEndOfLevelTriggerBehaviourScript::onUpdate() {}

void DemoEndOfLevelTriggerBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject != nullptr)
	{
		std::cout << "End of level trigger collided" << std::endl;

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
