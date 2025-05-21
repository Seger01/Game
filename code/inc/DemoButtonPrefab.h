#pragma once

#include <Components/Sprite.h>
#include <GameObject.h>
#include <SpriteDef.h>

class DemoButtonPrefab
{
public:
	DemoButtonPrefab();
	GameObject* createButtonPrefab();
	void addSprite(GameObject* gameObject);
	void addCollider(GameObject* gameObject);
	void addRigidBody(GameObject* gameObject);

private:
	SpriteDef mButtonUpSpriteDef;
	SpriteDef mButtonDownSpriteDef;
	Sprite* mButtonDownSprite = nullptr;
	Sprite* mButtonUpSprite = nullptr;
};
