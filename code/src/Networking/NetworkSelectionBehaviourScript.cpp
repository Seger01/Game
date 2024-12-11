#include "NetworkSelectionBehaviourScript.h"

#include "InitBehaviourScript.h"
#include "NetworkSelectionButtonScript.h"

#include "Button.h"
#include "Engine/EngineBravo.h"
#include "LevelManagerBehaviourScript.h"
#include "MainMenuPrefab.h"
#include "Network/NetworkClient.h"
#include "Network/NetworkManager.h"
#include "NetworkManager.h"
#include "PlayerPrefab.h"
#include "Text.h"

void NetworkSelectionBehaviourScript::onStart()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();

	GameObject* MainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();
	int menuIndexX = mMenuStartX;
	int menuIndexY = mMenuStartY;

	mServerButton = MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Server", "ServerButton",
																"ServerText", menuIndexX, menuIndexY);

	mSearchButton = MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "SearchServer", "SearchButton",
																"SearchServerText", menuIndexX, menuIndexY);
	mSearchButton->setActive(false);

	menuIndexY += 20;

	mClientButton = MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Client", "ClientButton",
																"ClientText", menuIndexX, menuIndexY);
	menuIndexY += 20;

	mHostButton = MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Host", "HostButton", "HostText",
															  menuIndexX, menuIndexY);
	menuIndexY += 20;
	scene->addGameObject(MainMenuObject);

	for (GameObject* button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("ServerButton"))
	{
		Button* buttonObject = dynamic_cast<Button*>(button);
		buttonObject->setOnReleaseCallback(std::bind(&NetworkSelectionBehaviourScript::onServerRelease, this));
	}
	for (GameObject* button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("ClientButton"))
	{
		Button* buttonObject = dynamic_cast<Button*>(button);
		buttonObject->setOnReleaseCallback(std::bind(&NetworkSelectionBehaviourScript::onClientRelease, this));
	}
	for (GameObject* button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("HostButton"))
	{
		Button* buttonObject = dynamic_cast<Button*>(button);
		buttonObject->setOnReleaseCallback(std::bind(&NetworkSelectionBehaviourScript::onHostRelease, this));
	}
	for (GameObject* button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("SearchButton"))
	{
		Button* buttonObject = dynamic_cast<Button*>(button);
		buttonObject->setOnReleaseCallback(std::bind(&NetworkSelectionBehaviourScript::onSearchRelease, this));
	}
}

void NetworkSelectionBehaviourScript::onUpdate()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	NetworkManager& networkManager = engine.getNetworkManager();

	if (networkManager.getRole() == NetworkRole::CLIENT)
	{
		if (networkManager.isConnected())
		{
			networkManager.setDefaultPlayerPrefab(PlayerPrefabFactory::createPlayerPrefab());
			for (GameObject* object :
				 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager"))
			{
				if (object->hasComponent<LevelManagerBehaviourScript>())
				{
					object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
				}
			}
		}
		else
		{
			mServerButton->setActive(false);
			mClientButton->setActive(false);
			mHostButton->setActive(false);
			mSearchButton->setActive(true);
		}
	}
}

void NetworkSelectionBehaviourScript::onServerRelease()
{
	NetworkManager& networkManager = EngineBravo::getInstance().getNetworkManager();
	std::cout << "Server selected" << std::endl;
	if (networkManager.isConnected())
	{
		std::cout << "Network is already connected" << std::endl;
	}
	else
	{
		networkManager.setRole(NetworkRole::SERVER);
		networkManager.startNetwork();
	}
	networkManager.setDefaultPlayerPrefab(PlayerPrefabFactory::createPlayerPrefab());
	for (GameObject* object :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager"))
	{
		if (object->hasComponent<LevelManagerBehaviourScript>())
		{
			object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
		}
	}
}

void NetworkSelectionBehaviourScript::onClientRelease()
{
	NetworkManager& networkManager = EngineBravo::getInstance().getNetworkManager();
	std::cout << "Client selected" << std::endl;
	if (networkManager.isConnected())
	{
		std::cout << "Network is already connected" << std::endl;
	}
	else
	{
		networkManager.setRole(NetworkRole::CLIENT);
		networkManager.startNetwork();
		NetworkClient& networkClient = EngineBravo::getInstance().getNetworkManager().getClient();
		networkClient.discoverServers();
		// mSearchServers = true;
		for (GameObject* button :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("ServerButton"))
		{
			Button* buttonObject = dynamic_cast<Button*>(button);
			buttonObject->setInteractable(false);
		}
		for (GameObject* button :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("ClientButton"))
		{
			Button* buttonObject = dynamic_cast<Button*>(button);
			buttonObject->setInteractable(false);
		}
		for (GameObject* button :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("HostButton"))
		{
			Button* buttonObject = dynamic_cast<Button*>(button);
			buttonObject->setInteractable(false);
		}
		for (GameObject* button :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("SearchButton"))
		{
			Button* buttonObject = dynamic_cast<Button*>(button);
			buttonObject->setActive(true);
		}
	}
}

void NetworkSelectionBehaviourScript::onHostRelease()
{
	NetworkManager& networkManager = EngineBravo::getInstance().getNetworkManager();
	std::cout << "Host selected" << std::endl;
	if (networkManager.isConnected())
	{
		std::cout << "Network is already connected" << std::endl;
	}
	else
	{
		networkManager.setRole(NetworkRole::HOST);
		networkManager.startNetwork();
	}
}

void NetworkSelectionBehaviourScript::onSearchRelease()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	NetworkManager& networkManager = engine.getNetworkManager();
	if (networkManager.isConnected())
	{
		networkManager.setDefaultPlayerPrefab(PlayerPrefabFactory::createPlayerPrefab());
		for (GameObject* object :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager"))
		{
			if (object->hasComponent<LevelManagerBehaviourScript>())
			{
				object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
			}
		}
	}
	NetworkClient& networkClient = engine.getNetworkManager().getClient();
	// networkClient.discoverServers();
	std::vector<std::string> serverAddresses = networkClient.getServerAddresses();
	int i{0};
	for (std::string serverAddress : serverAddresses)
	{
		int menuIndexX = mMenuStartX;
		int menuIndexY = mMenuStartY;

		int buttonHeight;
		int buttonWidth;

		Button* ipButton = new Button;
		ipButton->setTransform(Transform(Vector2(menuIndexX, menuIndexY)));
		menuIndexY += 20;
		ipButton->setTag(serverAddress);
		Text* ipText = new Text(serverAddress, serverAddress, Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
		ipText->setParent(ipButton);
		ipButton->addComponent<ConnectButtonScript>(ipText);
		engine.getRenderSystem().getTextSize(serverAddress, serverAddress, buttonWidth, buttonHeight,
											 Vector2(0.5, 0.5));
		ipButton->setWidth(buttonWidth);
		ipButton->setHeight(buttonHeight);

		Scene* scene = sceneManager.getCurrentScene();
		scene->addGameObject(ipButton);
		scene->addGameObject(ipText);

		++i;
	}
}

void NetworkSelectionBehaviourScript::onConnectRelease(const std::string& aServerAdress)
{
	std::cout << "Connect button released" << std::endl;
	NetworkClient& networkClient = EngineBravo::getInstance().getNetworkManager().getClient();
	networkClient.setServerAddress(aServerAdress);
	networkClient.connectToServer();
}