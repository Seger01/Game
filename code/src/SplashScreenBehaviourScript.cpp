#include "SplashScreenBehaviourScript.h"

#include <EngineBravo.h>
#include "SplashScreenPrefab.h"
#include "InitBehaviourScript.h"

#include <iostream>

void SplashScreenBehaviourScript::onStart()
{
    std::cout << "SplashScreenBehaviourScript::onStart()" << std::endl;
    SceneManager &sceneManager = EngineBravo::getInstance().getSceneManager();

    Scene *initScene = sceneManager.createScene("UnqiueSceneName");
    GameObject *initObject = new GameObject;
    initObject->addComponent<InitBehaviourScript>();

    int cameraID = initScene->addCamera();
    initScene->setActiveCamera(cameraID);
    initScene->getActiveCamera().setTransform(Transform(Vector2(80, 96)));
    initScene->getActiveCamera().setWidth(16 * 30);
    initScene->getActiveCamera().setHeight(9 * 30);

    Scene *splashScreenScene = sceneManager.getCurrentScene();
    GameObject *splashScreen = SplashScreenPrefab::create();
    splashScreenScene->addGameObject(splashScreen);

    startTime = std::chrono::system_clock::now();
}

void SplashScreenBehaviourScript::onUpdate()
{
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - startTime;

    if (elapsedTime.count() > 3)
    {
        SceneManager &sceneManager = EngineBravo::getInstance().getSceneManager();
        sceneManager.requestSceneChange("UnqiueSceneName");
    }
}