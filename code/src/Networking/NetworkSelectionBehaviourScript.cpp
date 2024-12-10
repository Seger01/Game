#include "NetworkSelectionBehaviourScript.h"

#include "InitBehaviourScript.h"
#include "NetworkSelectionButtonScript.h"

#include "Button.h"
#include "Engine/EngineBravo.h"
#include "LevelManagerBehaviourScript.h"
#include "MainMenuPrefab.h"
#include "Network/NetworkClient.h"
#include "Network/NetworkManager.h"
#include "PlayerPrefab.h"
#include "Text.h"

void NetworkSelectionBehaviourScript::onStart() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

	GameObject* MainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();
	int menuStartX = 240 + 13;
	int menuStartY = 135 + 5;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Server", "ServerButton", "ServerText",
												menuStartX, menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Client", "ClientButton", "ClientText",
												menuStartX, menuStartY);
	menuStartY += 20;

	MainMenuPrefabFactory().createDefaultButton(MainMenuObject, scene, "Host", "HostButton", "HostText", menuStartX,
												menuStartY);
	menuStartY += 20;

	Button* searchButton = MainMenuPrefabFactory().createDefaultButton(
		MainMenuObject, scene, "SearchServer", "SearchButton", "SearchServerText", menuStartX, menuStartY);
	searchButton->setInteractable(false);
	// Text* searchButtonText = searchButton->getComponents<Text>()[0];
	// searchButtonText->setActive(false);
	scene->addGameObject(MainMenuObject);
}

void NetworkSelectionBehaviourScript::onUpdate() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    NetworkManager& networkManager = engine.getNetworkManager();

    if (networkManager.getRole() == NetworkRole::SERVER || networkManager.getRole() == NetworkRole::HOST) {
        networkManager.setDefaultPlayerPrefab(PlayerPrefabFactory::createPlayerPrefab());
        for (GameObject* object :
             EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager")) {
            if (object->hasComponent<LevelManagerBehaviourScript>()) {
                object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
            }
        }
    }
    if (networkManager.getRole() == NetworkRole::CLIENT) {
        if (networkManager.isConnected()) {
            networkManager.setDefaultPlayerPrefab(PlayerPrefabFactory::createPlayerPrefab());
            for (
                GameObject* object :
                EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager")) {
                if (object->hasComponent<LevelManagerBehaviourScript>()) {
                    object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
                }
            }
        }
        NetworkClient& networkClient = engine.getNetworkManager().getClient();
        std::vector<std::string> serverAddresses = networkClient.getServerAddresses();
        for (std::string serverAddress : serverAddresses) {
            auto it = std::find(mServerAddresses.begin(), mServerAddresses.end(), serverAddress);
            if (it == mServerAddresses.end()) {
                // Server address not found
                mServerAddresses.push_back(serverAddress);

                int buttonHeight;
                int buttonWidth;

                Button* ipButton = new Button;
                ipButton->setTransform(Transform(Vector2(100, mServerAddresses.size() * 20)));
                ipButton->setTag(serverAddress);
                Text* ipText =
                    new Text(serverAddress, serverAddress, Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
                ipText->setParent(ipButton);
                ipButton->addComponent<ConnectButtonScript>(ipText);
                engine.getRenderSystem().getTextSize(serverAddress, serverAddress, buttonWidth, buttonHeight,
                                                     Vector2(0.5, 0.5));
                ipButton->setWidth(buttonWidth);
                ipButton->setHeight(buttonHeight);

                Scene* scene = sceneManager.getCurrentScene();
                scene->addGameObject(ipButton);
                scene->addGameObject(ipText);
            }
        }
    }
}
