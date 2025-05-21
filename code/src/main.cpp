#include <iostream>

#include "Components/IBehaviourScript.h"
#include "Components/ParticleEmitter.h"
#include "Components/RigidBody.h"
#include "Input/Input.h"
#include "SplashScreenBehaviourScript.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Scene.h>

void init()
{
	EngineBravo::getInstance().initialize();
	SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();

	Scene& scene = sceneManager.createScene("SplashScreenScene");
	GameObject* initObject = new GameObject;
	initObject->addComponent<SplashScreenBehaviourScript>();
	initObject->setTag("initObject");

	GameObject* temp = new GameObject;
	temp->setTag("temp");

	// scene->addGameObject(temp);
	scene.addGameObject(initObject);
	Camera* camera = new Camera;
	camera->setTag("MainCamera");
	camera->setActive(true);

	camera->setTransform(Transform(Vector2(100, 100)));
	camera->setWidth(200);
	camera->setHeight(200);

	scene.addGameObject(camera);

	sceneManager.requestSceneChange("SplashScreenScene");

	EngineBravo::getInstance().run();

	return;
}

int main()
{
	init();
	return 0;
}
