#include "NetworkSelectionBehaviourScript.h"

#include "InitBehaviourScript.h"
#include "NetworkSelectionButtonScript.h"

#include "Button.h"
#include "Engine/EngineBravo.h"
#include "LevelManagerBehaviourScript.h"
#include "Network/NetworkClient.h"
#include "Network/NetworkManager.h"
#include "Text.h"

void NetworkSelectionBehaviourScript::onStart() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    int buttonHeight;
    int buttonWidth;

    mServerButton = new Button;
    mServerButton->setTransform(Transform(Vector2(0, 0)));
    mServerButton->addComponent<NetworkSelectionButtonScript>();
    mServerButton->setTag("Server");
    Text* serverText = new Text("Server", "Server", Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
    serverText->setParent(mServerButton);
    engine.getRenderSystem().getTextSize("Server", "Server", buttonWidth, buttonHeight, Vector2(0.5, 0.5));
    mServerButton->setWidth(buttonWidth);
    mServerButton->setHeight(buttonHeight);

    mClientButton = new Button;
    mClientButton->setTransform(Transform(Vector2(0, 20)));
    mClientButton->addComponent<NetworkSelectionButtonScript>();
    mClientButton->setTag("Client");
    Text* clientText = new Text("Client", "Client", Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
    clientText->setParent(mClientButton);
    engine.getRenderSystem().getTextSize("Client", "Client", buttonWidth, buttonHeight, Vector2(0.5, 0.5));
    mClientButton->setWidth(buttonWidth);
    mClientButton->setHeight(buttonHeight);

    mHostButton = new Button;
    mHostButton->setTransform(Transform(Vector2(0, 40)));
    mHostButton->addComponent<NetworkSelectionButtonScript>();
    mHostButton->setTag("Host");
    Text* hostText = new Text("Host", "Host", Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
    hostText->setParent(mHostButton);
    engine.getRenderSystem().getTextSize("Host", "Host", buttonWidth, buttonHeight, Vector2(0.5, 0.5));
    mHostButton->setWidth(buttonWidth);
    mHostButton->setHeight(buttonHeight);

    mSearchButton = new Button;
    mSearchButton->setTransform(Transform(Vector2(0, 60)));
    mSearchButton->addComponent<NetworkSelectionButtonScript>();
    mSearchButton->setTag("Search");
    mSearchButton->setInteractable(false);
    Text* connectText = new Text("Connect", "Connect", Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
    connectText->setParent(mSearchButton);
    connectText->setActive(false);
    engine.getRenderSystem().getTextSize("Connect", "Connect", buttonWidth, buttonHeight, Vector2(0.5, 0.5));
    mSearchButton->setWidth(buttonWidth);
    mSearchButton->setHeight(buttonHeight);

    scene->addGameObject(mServerButton);
    scene->addGameObject(mClientButton);
    scene->addGameObject(mHostButton);
    scene->addGameObject(mSearchButton);

    scene->addGameObject(serverText);
    scene->addGameObject(clientText);
    scene->addGameObject(hostText);
    scene->addGameObject(connectText);
}

void NetworkSelectionBehaviourScript::onUpdate() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    NetworkManager& networkManager = engine.getNetworkManager();

    if (networkManager.getRole() == NetworkRole::SERVER || networkManager.getRole() == NetworkRole::HOST) {
        for (GameObject* object :
             EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("LevelManager")) {
            if (object->hasComponent<LevelManagerBehaviourScript>()) {
                object->getComponents<LevelManagerBehaviourScript>()[0]->beginDemoNetworkingGame();
            }
        }
    }
    if (networkManager.getRole() == NetworkRole::CLIENT) {
        if (networkManager.isConnected()) {
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
