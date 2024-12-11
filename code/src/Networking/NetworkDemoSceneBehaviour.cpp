#include "NetworkDemoSceneBehaviour.h"

#include "EnemyPrefab.h"

#include <EngineBravo.h>
#include <Input.h>
#include <iostream>

NetworkDemoSceneBehaviour::NetworkDemoSceneBehaviour() : IBehaviourScript("NetworkDemoSceneBehaviour") {}

NetworkDemoSceneBehaviour::NetworkDemoSceneBehaviour(const NetworkDemoSceneBehaviour& other) : IBehaviourScript(other)
{
}

void NetworkDemoSceneBehaviour::onUpdate()
{
	if (EngineBravo::getInstance().getNetworkManager().isServer())
	{
		if (Input::getInstance().GetKeyDown(Key::Key_Space))
		{
			std::cout << "Creating enemy" << std::endl;
			EngineBravo& engine = EngineBravo::getInstance();
			NetworkManager& networkManager = engine.getNetworkManager();
			EnemyPrefab enemyPrefab;
			networkManager.instantiate(enemyPrefab.getPrefabID(), Transform(Vector2(128, 112)));
		}
	}
}