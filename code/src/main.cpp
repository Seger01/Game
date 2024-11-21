#include <iostream>

#include "InitBehaviourScript.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>

void initScene() {
  EngineBravo &engine = EngineBravo::getInstance();
  engine.initialize();
  SceneManager &sceneManager = engine.getSceneManager();

  Scene *scene = sceneManager.createScene("InitScene");
  GameObject *initObject = new GameObject;
  initObject->addComponent<InitBehaviourScript>();

  scene->addGameObject(initObject);

  int cameraID = scene->addCamera();
  scene->setActiveCamera(cameraID);

  scene->getActiveCamera().setTransform(Transform(Vector2(80, 96)));
  scene->getActiveCamera().setWidth(16 * 30);
  scene->getActiveCamera().setHeight(9 * 30);

  sceneManager.requestSceneChange("InitScene");

  engine.run();

  return;
}
int main() {
  initScene();
  return 0;
}