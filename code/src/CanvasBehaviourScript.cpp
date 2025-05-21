#include "CanvasBehaviourScript.h"

#include <Engine/EngineBravo.h>
#include <UI/Button.h>
// #include <FPSCounterBehaviourScript.h>
// #include "HelloWorldButtonBehaviour.h"
#include "PlayerStatsBehaviourScript.h"
// #include <FPSCounterBehaviourScript.h>
// #include "HelloWorldButtonBehaviour.h"
// #include "PlayerStatsBehaviourScript.h"
#include <UI/Text.h>

// #include "Network/NetworkObject.h"

// SpriteDef buttonSpriteDef = {"UI/ui_images.png", Rect{0, 287, 64, 16}, 64, 16};

void CanvasBehaviourScript::onStart()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene& scene = sceneManager.getCurrentScene();
	Camera* camera = scene.getCameraWithTag("MainCamera");

	// Button* buttonObject = new Button;
	// buttonObject->setTransform(Transform(Vector2(10, 50)));
	// buttonObject->addComponent<HelloWorldButtonBehaviour>();

	// Text* buttonText = new Text("Button1", "werkt niet", Color(15, 110, 47), Vector2(0, 0), Vector2(0.5, 0.5));
	// buttonText->setParent(buttonObject);
	// buttonObject->setWidth(40);
	// buttonObject->setHeight(10);
	// buttonObject->setParent(mGameObject);

	// GameObject* textObject = new Text("Canvas", "undefined", Color(15, 110, 47), Vector2(10, 10), Vector2(1, 1));
	// textObject->setParent(mGameObject);

	GameObject* playerStats = new GameObject;
	playerStats->addComponent<PlayerStatsBehaviourScript>();
	playerStats->setTransform(Transform(Vector2(5, camera->getHeight() - 45)));
	playerStats->setParent(*mGameObject);

	scene.addGameObject(playerStats);
	// scene->addGameObject(textObject);
	// scene->addGameObject(buttonObject);
	// scene->addGameObject(buttonText);

	return;
}

void CanvasBehaviourScript::onUpdate()
{

	Camera* camera = EngineBravo::getInstance().getSceneManager().getCurrentScene().getCameraWithTag("MainCamera");
	if (!camera->hasParent())
	{
		mGameObject->setParent(*camera);
		mGameObject->setTransform(Transform(Vector2(-(camera->getWidth() / 2), -(camera->getHeight() / 2))));
	}
}

void CanvasBehaviourScript::onCollide(GameObject* aGameObject)
{
	// std::cout << "CanvasBehaviourScript collided with " << aGameObject->getName() << std::endl;
}
