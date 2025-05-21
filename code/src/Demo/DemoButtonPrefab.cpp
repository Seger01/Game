#include "DemoButtonPrefab.h"
#include <Components/BoxCollider.h>
#include <Components/RigidBody.h>
#include <Components/Sprite.h>
#include <Engine/EngineBravo.h>
#include <SpriteDef.h>

// SpriteDef buttonUpSpriteDef =
// SpriteDef buttonDownSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{32, 208, 16, 16}, 16, 16};
// Sprite* buttonDownSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonDownSpriteDef);
// Sprite* buttonUpSprite = EngineBravo::getInstance().getResourceManager().createSprite(buttonUpSpriteDef);

DemoButtonPrefab::DemoButtonPrefab()
{
	mButtonUpSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{16, 208, 16, 16}, 16, 16};
	mButtonDownSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{32, 208, 16, 16}, 16, 16};
	mButtonDownSprite = EngineBravo::getInstance().getResourceManager().createSprite(mButtonDownSpriteDef);
	mButtonUpSprite = EngineBravo::getInstance().getResourceManager().createSprite(mButtonUpSpriteDef);
}

GameObject* DemoButtonPrefab::createButtonPrefab()
{
	GameObject* button = new GameObject;
	addSprite(button);
	addCollider(button);
	addRigidBody(button);
	return button;
}

void DemoButtonPrefab::addRigidBody(GameObject* gameObject)
{
	RigidBody* rigidBody = new RigidBody();
	// rigidBody->setTransform(gameObject->getTransform());
	// rigidBody->setDensity(1.0f);
	gameObject->addComponent(rigidBody);
}

void DemoButtonPrefab::addCollider(GameObject* gameObject)
{
	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->setWidth(mButtonUpSprite->getWidth());
	boxCollider->setHeight(mButtonUpSprite->getHeight());
	boxCollider->setTrigger(true);

	gameObject->addComponent(boxCollider);
}

void DemoButtonPrefab::addSprite(GameObject* gameObject)
{
	mButtonDownSprite->setLayer(1);
	mButtonDownSprite->setTag("ButtonDownSprite");
	mButtonDownSprite->setActive(false);
	mButtonUpSprite->setLayer(1);
	mButtonUpSprite->setTag("ButtonUpSprite");
	mButtonDownSprite->setActive(true);

	gameObject->addComponent(mButtonDownSprite);
	gameObject->addComponent(mButtonUpSprite);
}
