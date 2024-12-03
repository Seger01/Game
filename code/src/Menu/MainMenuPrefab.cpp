#include "MainMenuPrefab.h"

#include "Button.h"
#include "GameObject.h"
#include "MainMenuBehaviourScript.h"
#include "MainMenuButtonBehaviour.h"
#include "SpriteDef.h"
#include "Text.h"
#include <EngineBravo.h>

SpriteDef menuBackgroundSpriteDef = {"UI/MenuScreen.png", Rect(), 100, 100};
SpriteDef buttonSpriteDef = {"UI/ui_images.png", Rect{145, 81, 46, 14}, 46, 14};

GameObject* MainMenuPrefabFactory::createMainMenuPrefab()
{
	GameObject* mainMenuPrefab = new GameObject;
	setTag(mainMenuPrefab);
	setBackground(mainMenuPrefab);
	addBehaviour(mainMenuPrefab);

	mainMenuPrefab->setTransform(Transform(Vector2(0, 0)));
	return mainMenuPrefab;
}

void MainMenuPrefabFactory::setTag(GameObject* gameObject) { gameObject->setTag("MainMenu"); }

void MainMenuPrefabFactory::setBackground(GameObject* gameObject)
{
	Sprite* backgroundSprite = EngineBravo::getInstance().getResourceManager().createSprite(menuBackgroundSpriteDef);

	backgroundSprite->setLayer(0);

	Camera* camera = EngineBravo::getInstance().getSceneManager().getCurrentScene()->getCameraWithTag("MainCamera");

	backgroundSprite->setWidth(camera->getWidth());
	backgroundSprite->setHeight(camera->getHeight());

	gameObject->addComponent(backgroundSprite);
}

void MainMenuPrefabFactory::addBehaviour(GameObject* gameObject)
{
	gameObject->addComponent<MainMenuBehaviourScript>();
}

Button* MainMenuPrefabFactory::createDefaultButton(GameObject* gameObject, Scene* aScene, const std::string& text,
												   const std::string& tag, const std::string& buttonText,
												   int menuStartX, int menuStartY)
{
	EngineBravo& engine = EngineBravo::getInstance();
	Button* buttonObject = new Button;
	buttonObject->setTag(tag);

	buttonObject->addComponent<MainMenuButtonBehaviour>();
	buttonObject->setParent(gameObject);
	Text* buttonTextObj = new Text(text, "werkt niet", Color(255, 255, 255), Vector2(0, 0), Vector2(0.5, 0.5));
	buttonTextObj->setLayer(2);
	buttonTextObj->setParent(buttonObject);
	buttonTextObj->setTag(buttonText);

    Sprite* buttonSprite = engine.getResourceManager().createSprite(buttonSpriteDef);
    buttonSprite->setLayer(1);
    buttonObject->addComponent(buttonSprite);
    int width = 0;
    int height = 0;
    buttonSprite->setColorFilter({255, 255, 255, 100});
    engine.getRenderSystem().getTextSize(buttonTextObj->getFont(), buttonTextObj->getText(), width, height,
                                         buttonTextObj->getScale());
    width += 2;
    height += 2;
    buttonSprite->setWidth(width);
    buttonSprite->setHeight(height);
    buttonSprite->setRelativePosition(Transform(Vector2(-1, -1)));

	buttonObject->setWidth(width);
	buttonObject->setHeight(height);

	buttonObject->setTransform(
		Transform(Vector2(menuStartX - (buttonObject->getWidth() / 2), menuStartY - (buttonObject->getHeight() / 2))));

	aScene->addGameObject(buttonObject);
	aScene->addGameObject(buttonTextObj);

	return buttonObject;
}
