#include "MainMenuBehaviourScript.h"

#include "DemoManagerBehaviourScript.h"
#include "EngineBravo.h"
#include "LevelManagerBehaviourScript.h"
#include "NetworkSelectionBehaviourScript.h"

MainMenuBehaviourScript::MainMenuBehaviourScript() {}

MainMenuBehaviourScript::~MainMenuBehaviourScript() {}

void MainMenuBehaviourScript::onStart()
{
	for (GameObject& button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("PlayButton"))
	{
		Button& buttonObject = dynamic_cast<Button&>(button);
		buttonObject.setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onPlayRelease, this));
	}
	for (GameObject& button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("MultiplayerButton"))
	{
		Button& buttonObject = dynamic_cast<Button&>(button);
		buttonObject.setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onMultiplayerRelease, this));
	}
	for (GameObject& button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("DemoButton"))
	{
		Button& buttonObject = dynamic_cast<Button&>(button);
		buttonObject.setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onDemoRelease, this));
	}
	for (GameObject& button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("ExitButton"))
	{
		Button& buttonObject = dynamic_cast<Button&>(button);
		buttonObject.setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onExitRelease, this));
	}
	for (GameObject& button :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("DemoMultiButton"))
	{
		Button& buttonObject = dynamic_cast<Button&>(button);
		buttonObject.setOnReleaseCallback(std::bind(&MainMenuBehaviourScript::onDemoMultiRelease, this));
	}
}

void MainMenuBehaviourScript::onUpdate() {}

void MainMenuBehaviourScript::onPlayRelease()
{
	std::cout << "Wanted to play the game" << std::endl;
	for (GameObject& object :
		 EngineBravo::getInstance().getSceneManager().getCurrentScene().getGameObjectsWithTag("LevelManager"))
	{
		if (object.hasComponent<LevelManagerBehaviourScript>())
		{
			object.getComponents<LevelManagerBehaviourScript>()[0].get().beginGame();
		}
	}
}

void MainMenuBehaviourScript::onMultiplayerRelease() { std::cout << "Wanted to multiplayer" << std::endl; }

void MainMenuBehaviourScript::onDemoRelease()
{
	GameObject& demoManagerObject = *(new GameObject);
	demoManagerObject.addComponent<DemoManagerBehaviourScript>();
	demoManagerObject.setTag("DemoManager");

	Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();

	std::cout << "Current scene: " << scene.getName() << std::endl;

	scene.addPersistentGameObject(&demoManagerObject);

	std::cout << "Wanted to play demo" << std::endl;
}

void MainMenuBehaviourScript::onExitRelease() { std::cout << "adfljasdflkjafds to exit game" << std::endl; }

void MainMenuBehaviourScript::onDemoMultiRelease()
{
	std::cout << "Wanted to play demo multiplayer" << std::endl;
	Scene& scene = EngineBravo::getInstance().getSceneManager().createScene("networkSelectionScene");
	GameObject& networkSelectionObject = *(new GameObject);
	networkSelectionObject.addComponent<NetworkSelectionBehaviourScript>();
	scene.addGameObject(&networkSelectionObject);

	Camera* camera =
		new Camera(*EngineBravo::getInstance().getSceneManager().getCurrentScene().getCameraWithTag("MainCamera"));
	camera->setTag("MainCamera");
	camera->setActive(true);

	scene.addGameObject(camera);

	EngineBravo::getInstance().getSceneManager().requestSceneChange("networkSelectionScene");
}
