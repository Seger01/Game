#include <iostream>

#include "SplashScreenBehaviourScript.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>

void init()
{
	EngineBravo::getInstance().initialize();
	SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();

	Scene* scene = sceneManager.createScene("SplashScreenScene");
	GameObject* initObject = new GameObject;
	initObject->addComponent<SplashScreenBehaviourScript>();
	initObject->setTag("initObject");

	GameObject* temp = new GameObject;
	temp->setTag("temp");

	// scene->addGameObject(temp);
	scene->addGameObject(initObject);
	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(100, 100)));
	camera->setWidth(200);
	camera->setHeight(200);

	scene->addGameObject(camera);

	sceneManager.requestSceneChange("SplashScreenScene");

	EngineBravo::getInstance().run();

	return;
}

int main()
{
	init();
	return 0;
}
