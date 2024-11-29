#include "InitBehaviourScript.h"
#include "LevelManagerBehaviourScript.h"
#include "LevelManagerPrefab.h"
#include "MainMenuButtonBehaviour.h"
#include "MainMenuPrefab.h"
#include "Text.h"
#include <EngineBravo.h>
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <iostream>

SpriteDef buttonSpriteDef = {"UI/ui_images.png", Rect{145, 81, 46, 14}, 46, 14};

void InitBehaviourScript::onStart() { createLevelManager(); }

void InitBehaviourScript::onUpdate() {}

void InitBehaviourScript::createLevelManager() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    GameObject* LevelManagerObject = LevelManagerFactory().createLevelManagerPrefab();

    scene->addPersistentGameObject(LevelManagerObject);

    createMainMenu();
    // LevelManagerBehaviourScript* levelManager =
    // LevelManagerObject->getComponents<LevelManagerBehaviourScript>()[0];
    // levelManager->beginGame();
}

void InitBehaviourScript::createMainMenu() {
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.createScene("MainMenuScene");

    int menuStartX = 240 + 13;
    int menuStartY = 135 + 5;

    GameObject* MainMenuObject = MainMenuPrefabFactory().createMainMenuPrefab();

    {
        Button* buttonObject = new Button;
        buttonObject->setTag("PlayButton");

        buttonObject->addComponent<MainMenuButtonBehaviour>();
        buttonObject->setParent(MainMenuObject);
        Text* buttonText = new Text("Play", "werkt niet", Color(255, 255, 255), Vector2(0, 0), Vector2(0.5, 0.5));
        buttonText->setLayer(2);
        buttonText->setParent(buttonObject);
        buttonText->setTag("PlayButtonText");

        Sprite* buttonSprite = engine.getResourceManager().createSprite(buttonSpriteDef);
        buttonSprite->setLayer(1);
        buttonObject->addComponent(buttonSprite);
        int width = 0;
        int height = 0;
        engine.getRenderSystem().getTextSize(buttonText->getFont(), buttonText->getText(), width, height,
                                             buttonText->getScale());
        width += 2;
        height += 2;
        buttonSprite->setWidth(width);
        buttonSprite->setHeight(height);
        buttonSprite->setRelativePosition(Transform(Vector2(-1, -1)));

        buttonObject->setWidth(width);
        buttonObject->setHeight(height);

        buttonObject->setTransform(Transform(
            Vector2(menuStartX - (buttonObject->getWidth() / 2), menuStartY - (buttonObject->getHeight() / 2))));

        scene->addGameObject(buttonObject);
        scene->addGameObject(buttonText);
    }
    menuStartY += 20;
    {
        Button* buttonObject = new Button;
        buttonObject->setTag("MultiplayerButton");

        buttonObject->addComponent<MainMenuButtonBehaviour>();
        buttonObject->setParent(MainMenuObject);
        Text* buttonText =
            new Text("Multiplayer", "werkt niet", Color(255, 255, 255), Vector2(0, 0), Vector2(0.5, 0.5));
        buttonText->setTag("MultiplayerButtonText");
        buttonText->setLayer(2);
        buttonText->setParent(buttonObject);
        buttonText->setLayer(2);

        Sprite* buttonSprite = engine.getResourceManager().createSprite(buttonSpriteDef);
        buttonSprite->setLayer(1);
        buttonObject->addComponent(buttonSprite);
        int width = 0;
        int height = 0;
        engine.getRenderSystem().getTextSize(buttonText->getFont(), buttonText->getText(), width, height,
                                             buttonText->getScale());
        width += 2;
        height += 2;
        buttonSprite->setWidth(width);
        buttonSprite->setHeight(height);
        buttonSprite->setRelativePosition(Transform(Vector2(-1, -1)));

        buttonObject->setWidth(width);
        buttonObject->setHeight(height);

        buttonObject->setTransform(Transform(
            Vector2(menuStartX - (buttonObject->getWidth() / 2), menuStartY - (buttonObject->getHeight() / 2))));

        scene->addGameObject(buttonObject);
        scene->addGameObject(buttonText);
    }
    menuStartY += 20;
    {
        Button* buttonObject = new Button;
        buttonObject->setTag("DemoButton");

        buttonObject->addComponent<MainMenuButtonBehaviour>();
        buttonObject->setParent(MainMenuObject);
        Text* buttonText = new Text("Demo", "werkt niet", Color(255, 255, 255), Vector2(0, 0), Vector2(0.5, 0.5));
        buttonText->setTag("DemoButtonText");
        buttonText->setLayer(2);
        buttonText->setParent(buttonObject);
        buttonText->setLayer(2);

        Sprite* buttonSprite = engine.getResourceManager().createSprite(buttonSpriteDef);
        buttonSprite->setLayer(1);
        buttonObject->addComponent(buttonSprite);
        buttonSprite->setLayer(1);
        int width = 0;
        int height = 0;
        engine.getRenderSystem().getTextSize(buttonText->getFont(), buttonText->getText(), width, height,
                                             buttonText->getScale());
        width += 2;
        height += 2;
        buttonSprite->setWidth(width);
        buttonSprite->setHeight(height);
        buttonSprite->setRelativePosition(Transform(Vector2(-1, -1)));

        buttonObject->setWidth(width);
        buttonObject->setHeight(height);

        buttonObject->setTransform(Transform(
            Vector2(menuStartX - (buttonObject->getWidth() / 2), menuStartY - (buttonObject->getHeight() / 2))));

        scene->addGameObject(buttonObject);
        scene->addGameObject(buttonText);
    }
    menuStartY += 20;
    {
        Button* buttonObject = new Button;
        buttonObject->setTag("ExitButton");

        buttonObject->addComponent<MainMenuButtonBehaviour>();
        buttonObject->setParent(MainMenuObject);
        Text* buttonText = new Text("Exit", "werkt niet", Color(255, 255, 255), Vector2(0, 0), Vector2(0.5, 0.5));
        buttonText->setLayer(2);
        buttonText->setParent(buttonObject);
        buttonText->setTag("ExitButtonText");

        Sprite* buttonSprite = engine.getResourceManager().createSprite(buttonSpriteDef);
        buttonSprite->setLayer(1);
        buttonObject->addComponent(buttonSprite);
        int width = 0;
        int height = 0;
        engine.getRenderSystem().getTextSize(buttonText->getFont(), buttonText->getText(), width, height,
                                             buttonText->getScale());
        width += 2;
        height += 2;
        buttonSprite->setWidth(width);
        buttonSprite->setHeight(height);
        buttonSprite->setRelativePosition(Transform(Vector2(-1, -1)));

        buttonObject->setWidth(width);
        buttonObject->setHeight(height);

        buttonObject->setTransform(Transform(
            Vector2(menuStartX - (buttonObject->getWidth() / 2), menuStartY - (buttonObject->getHeight() / 2))));

        scene->addGameObject(buttonObject);
        scene->addGameObject(buttonText);
    }
    scene->addGameObject(MainMenuObject);

    int cameraID = scene->addCamera();
    scene->setActiveCamera(cameraID);

    scene->getActiveCamera().setTransform(Transform(Vector2((16 * 30) / 2, (9 * 30) / 2)));
    scene->getActiveCamera().setWidth(16 * 30);
    scene->getActiveCamera().setHeight(9 * 30);

    sceneManager.requestSceneChange("MainMenuScene");
}
