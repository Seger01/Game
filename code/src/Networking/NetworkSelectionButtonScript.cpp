#include "NetworkSelectionButtonScript.h"
#include "Button.h"
#include "Engine/EngineBravo.h"
#include "LevelManagerBehaviourScript.h"
#include "Network/NetworkManager.h"
#include "PlayerPrefab.h"
#include "Text.h"

#include <iostream>

ConnectButtonScript::ConnectButtonScript(Text* aTextObject) : mTextObject(aTextObject) {}

ConnectButtonScript::~ConnectButtonScript() {}

void ConnectButtonScript::onButtonPressed()
{
	std::cout << "Connect button pressed" << std::endl;
	NetworkClient& networkClient = EngineBravo::getInstance().getNetworkManager().getClient();
	networkClient.setServerAddress(mTextObject->getText());
	networkClient.connectToServer();
}

void ConnectButtonScript::onButtonReleased() {}
