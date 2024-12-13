#include "PlayerStatsBehaviourScript.h"
#include "EngineBravo.h"
#include "Input.h"
#include "PlayerBehaviourScript.h"

SpriteDef playerStatBackgroundDef = {"UI/ui_images.png", Rect{95, 35, 66, 26}, 99, 39};
SpriteDef playerStatHealthBarBackgroundDef = {"UI/ui_images.png", Rect{134, 19, 54, 9}, 81, 15};
SpriteDef playerStatHealthBarDef = {"UI/ui_images.png", Rect{72, 22, 49, 3}, 74, 5};
SpriteDef playerStatBSCountDef = {"Coins/Money.png", Rect(), 16, 16};

PlayerStatsBehaviourScript::PlayerStatsBehaviourScript() : mHealthBarWidth(0) {}

void PlayerStatsBehaviourScript::onStart()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();
	// Camera& camera = scene->getActiveCamera();

	Sprite* playerStatBackgroundSprite = engine.getResourceManager().createSprite(playerStatBackgroundDef);
	playerStatBackgroundSprite->setLayer(4);
	playerStatBackgroundSprite->setWidth(playerStatBackgroundSprite->getWidth());
	playerStatBackgroundSprite->setHeight(playerStatBackgroundSprite->getHeight());

	Sprite* playerStatHealthBarBackgroundSprite =
		engine.getResourceManager().createSprite(playerStatHealthBarBackgroundDef);
	playerStatHealthBarBackgroundSprite->setLayer(4);
	playerStatHealthBarBackgroundSprite->setWidth(playerStatHealthBarBackgroundSprite->getWidth());
	playerStatHealthBarBackgroundSprite->setHeight(playerStatHealthBarBackgroundSprite->getHeight());
	playerStatHealthBarBackgroundSprite->setRelativePosition(Transform(Vector2(39, 0)));

	// Sprite* playerStatHealthBarSprite = engine.getResourceManager().createSprite(playerStatHealthBarDef);
	// playerStatHealthBarSprite->setLayer(5);
	// playerStatHealthBarSprite->setWidth(playerStatHealthBarSprite->getWidth());
	// playerStatHealthBarSprite->setHeight(playerStatHealthBarSprite->getHeight());
	// playerStatHealthBarSprite->setRelativePosition(Transform(Vector2(42, 5)));
	// playerStatHealthBarSprite->setTag("playerHealthBar");

	Sprite* playerStatHealthBarSprite = engine.getResourceManager().createSprite(playerStatHealthBarDef);
	playerStatHealthBarSprite->setLayer(5);
	playerStatHealthBarSprite->setWidth(playerStatHealthBarSprite->getWidth());
	playerStatHealthBarSprite->setHeight(playerStatHealthBarSprite->getHeight());
	playerStatHealthBarSprite->setRelativePosition(Transform(Vector2(42, 5)));
	playerStatHealthBarSprite->setTag("playerHealthBar");

	Sprite* BSSprite = engine.getResourceManager().createSprite(playerStatBSCountDef);
	BSSprite->setLayer(5);
	BSSprite->setWidth(BSSprite->getWidth());
	BSSprite->setHeight(BSSprite->getHeight());
	BSSprite->setRelativePosition(Transform(Vector2(38, 22)));
	BSSprite->setTag("playerBSCount");

	mBSCountText = new Text("0", "Arial", Color(255, 255, 255), Vector2(0, 0), Vector2(1, 1)); // Adjust position and
																							   // scale as needed
	mBSCountText->setLayer(5);
	mBSCountText->setTag("playerBSCountText");
	mBSCountText->setParent(mGameObject);

	mGameObject->addComponent(playerStatBackgroundSprite);
	mGameObject->addComponent(playerStatHealthBarBackgroundSprite);
	mGameObject->addComponent(playerStatHealthBarSprite);
	mGameObject->addComponent(BSSprite);

	mHealthBarWidth = playerStatHealthBarSprite->getWidth();
	mFullHealthBarForegroundSourceRect = playerStatHealthBarSprite->getSource();

	GameObject& playerObject = scene->getGameObjectsWithTag("Player")[0];

	mPlayerBehaviourScript = &playerObject.getComponents<PlayerBehaviourScript>()[0].get();
}

void PlayerStatsBehaviourScript::onUpdate()
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	Scene* scene = sceneManager.getCurrentScene();

	if (mPlayerBehaviourScript == nullptr)
	{
		return;
	}

	GameObject* playerObject = &scene->getGameObjectsWithTag("Player")[0].get();
	if (playerObject == nullptr)
	{
		return;
	}

	if (playerObject->getComponentsWithTag<PlayerBehaviourScript>("PlayerBehaviourScript").size() == 0)
	{
		return;
	}
	float playerHealth = mPlayerBehaviourScript->getHealth();
	float playerMaxHealth = mPlayerBehaviourScript->getMaxHealth();
	int playerBSCount = mPlayerBehaviourScript->getBSCount();

	if (playerHealth > 0)
	{
		if (playerHealth < 0)
		{
			playerHealth = 0;
		}

		if (mGameObject->getComponentsWithTag<Sprite>("playerHealthBar").size() > 0)
		{
			Sprite* sprite = &mGameObject->getComponentsWithTag<Sprite>("playerHealthBar")[0].get();

			Rect sourceRect = sprite->getSource();
			sourceRect.w = mFullHealthBarForegroundSourceRect.w * (playerHealth / playerMaxHealth);

			if (sourceRect.w < 1)
			{
				sourceRect.w = 1;
			}

			sourceRect.x = mFullHealthBarForegroundSourceRect.x + mFullHealthBarForegroundSourceRect.w - sourceRect.w;
			sprite->setSource(sourceRect);

			sprite->setWidth(mHealthBarWidth * (playerHealth / playerMaxHealth));
		}
	}
	else
	{
		playerHealth = playerMaxHealth;
	}

	if (scene->getGameObjectsWithTag("playerBSCountText").size() > 0)
	{
		GameObject* gameObject = &scene->getGameObjectsWithTag("playerBSCountText")[0].get();
		dynamic_cast<Text*>(gameObject)->setText(std::to_string(playerBSCount));
	}
}

void PlayerStatsBehaviourScript::onCollide(GameObject* aGameObject)
{
	std::cout << "PlayerStatsBehaviourScript collided with " << aGameObject->getName() << std::endl;
}
