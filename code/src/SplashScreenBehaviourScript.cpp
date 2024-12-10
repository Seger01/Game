#include "SplashScreenBehaviourScript.h"

#include "InitBehaviourScript.h"
#include "Input.h"
#include "SplashScreenPrefab.h"
#include <EngineBravo.h>

#include <iostream>

SplashScreenBehaviourScript::SplashScreenBehaviourScript() : splashScreenPrefab(*(SplashScreenPrefab::create())) {}

void SplashScreenBehaviourScript::onStart()
{
	std::cout << "SplashScreenBehaviourScript::onStart()" << std::endl;
	SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();

	Scene* initScene = sceneManager.createScene("InitScene");
	GameObject* initObject = new GameObject;
	initObject->addComponent<InitBehaviourScript>();
	initScene->addGameObject(initObject);

	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(80, 96)));
	camera->setWidth(16 * 30);
	camera->setHeight(9 * 30);

	initScene->addGameObject(camera);

	Scene* splashScreenScene = sceneManager.getCurrentScene();
	splashScreenScene->addGameObject(&splashScreenPrefab);

	startTime = std::chrono::system_clock::now();
}

void SplashScreenBehaviourScript::onUpdate()
{
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = currentTime - startTime;
	Input& input = Input::getInstance();

	if (elapsedTime.count() > 2 || input.GetKeyDown(Key::Key_Space))
	{
		SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();
		sceneManager.requestSceneChange("InitScene");
	}
}
