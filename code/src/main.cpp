#include <iostream>

#include "SplashScreenBehaviourScript.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>

void init()
{
  EngineBravo::getInstance().initialize();
  SceneManager &sceneManager = EngineBravo::getInstance().getSceneManager();

  Scene *scene = sceneManager.createScene("InitScene");
  GameObject *initObject = new GameObject;
  initObject->addComponent<SplashScreenBehaviourScript>();

  scene->addGameObject(initObject);

  int cameraID = scene->addCamera();
  scene->setActiveCamera(cameraID);

  scene->getActiveCamera().setTransform(Transform(Vector2(100, 100)));
  scene->getActiveCamera().setWidth(200);
  scene->getActiveCamera().setHeight(200);

  sceneManager.requestSceneChange("InitScene");

  EngineBravo::getInstance().run();

  return;
}
int main() {
  init();
  return 0;
}