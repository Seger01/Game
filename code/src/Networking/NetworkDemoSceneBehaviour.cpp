#include "NetworkDemoSceneBehaviour.h"

#include "EnemyPrefab.h"

#include <Engine/EngineBravo.h>
#include <Input/Input.h>
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
			EngineBravo& engine = EngineBravo::getInstance();
			NetworkManager& networkManager = engine.getNetworkManager();
			EnemyPrefab enemyPrefab;
			networkManager.instantiate(enemyPrefab.getPrefabID(), Transform(Vector2(128, 112)));
		}
		if (Input::getInstance().GetKeyDown(Key::Key_LControl))
		{
			EngineBravo& engine = EngineBravo::getInstance();
			NetworkManager& networkManager = engine.getNetworkManager();
			for (auto gameObject : engine.getSceneManager().getCurrentScene().getGameObjects())
			{
				if (gameObject.get().hasComponent<NetworkObject>())
				{
					NetworkObject& networkObject = gameObject.get().getComponents<NetworkObject>()[0].get();
					if (networkObject.isOwner() && !networkObject.isPlayer())
					{
						networkManager.destroy(gameObject.get());
						break;
					}
				}
			}
		}
	}
}
