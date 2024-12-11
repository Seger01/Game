#include "NetworkSelectionBehaviourScript.h"

#include "InitBehaviourScript.h"

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

	// Create the menu
	mMainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();
	int menuIndexX = mMenuStartX;
	int menuIndexY = mMenuStartY;

	// Create the buttons
	mServerButton = MainMenuPrefabFactory().createDefaultButton(mMainMenuObject, scene, "Server", "ServerButton",
																"ServerText", menuIndexX, menuIndexY);

	mSearchButton = MainMenuPrefabFactory().createDefaultButton(
		mMainMenuObject, scene, "Search for servers", "SearchButton", "SearchServerText", menuIndexX, menuIndexY);
	mSearchButton->setActive(false);

	menuIndexY += 20;

	mClientButton = MainMenuPrefabFactory().createDefaultButton(mMainMenuObject, scene, "Client", "ClientButton",
																"ClientText", menuIndexX, menuIndexY);
	menuIndexY += 20;

	mHostButton = MainMenuPrefabFactory().createDefaultButton(mMainMenuObject, scene, "Host", "HostButton", "HostText",
															  menuIndexX, menuIndexY);
	menuIndexY += 20;
	scene->addGameObject(mMainMenuObject);

	// Add the button callbacks
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
		// If client is connected, load the networking demo
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
			// If client is selected but not yet connected, disable the other buttons
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

	for (Button* ipButton : mServerAdressButtons)
	{
		sceneManager.getCurrentScene()->requestGameObjectRemoval(ipButton);
	}
	mServerAdressButtons.clear();

	NetworkClient& networkClient = engine.getNetworkManager().getClient();
	std::vector<std::string> serverAddresses = networkClient.getServerAddresses();
	for (std::string serverAddress : serverAddresses)
	{
		int menuIndexX = mMenuStartX;
		int menuIndexY = mMenuStartY + 20;

		std::string buttonTag = "button" + serverAddress;
		mServerAdressButtons.push_back(
			MainMenuPrefabFactory::createDefaultButton(mMainMenuObject, sceneManager.getCurrentScene(), serverAddress,
													   buttonTag, serverAddress, menuIndexX, menuIndexY));

		for (GameObject* button :
			 EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag(buttonTag))
		{
			Button* buttonObject = dynamic_cast<Button*>(button);
			buttonObject->setOnReleaseCallback(
				std::bind(&NetworkSelectionBehaviourScript::onConnectRelease, this, serverAddress));
		}

		menuIndexY += 20;
	}
}

void NetworkSelectionBehaviourScript::onConnectRelease(const std::string& aServerAdress)
{
	std::cout << "Connect button released" << std::endl;
	NetworkClient& networkClient = EngineBravo::getInstance().getNetworkManager().getClient();
	networkClient.setServerAddress(aServerAdress);
	networkClient.connectToServer();
}