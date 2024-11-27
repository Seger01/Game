#include "MainMenuPrefab.h"

#include "EngineBravo.h"
#include "GameObject.h"
#include "MainMenuBehaviourScript.h"
#include "SpriteDef.h"

SpriteDef menuBackgroundSpriteDef = {"UI/MenuScreen.png", Rect(), 100, 100};

GameObject *MainMenuPrefabFactory::createMainMenuPrefab() {
  GameObject *mainMenuPrefab = new GameObject;
  setTag(mainMenuPrefab);
  setBackground(mainMenuPrefab);
  addBehaviour(mainMenuPrefab);

  mainMenuPrefab->setTransform(Transform(Vector2(0, 0)));
  return mainMenuPrefab;
}

void MainMenuPrefabFactory::setTag(GameObject *gameObject) {
  gameObject->setTag("MainMenu");
}

void MainMenuPrefabFactory::setBackground(GameObject *gameObject) {
  Sprite *backgroundSprite =
      EngineBravo::getInstance().getResourceManager().createSprite(
          menuBackgroundSpriteDef);

  backgroundSprite->setLayer(0);

  Camera &camera = EngineBravo::getInstance()
                       .getSceneManager()
                       .getCurrentScene()
                       ->getActiveCamera();

  backgroundSprite->setWidth(camera.getWidth());
  backgroundSprite->setHeight(camera.getHeight());

  gameObject->addComponent(backgroundSprite);
}

void MainMenuPrefabFactory::addBehaviour(GameObject *gameObject) {
  gameObject->addComponent<MainMenuBehaviourScript>();
}
