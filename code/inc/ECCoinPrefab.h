#pragma once

#include <Components/CircleCollider.h>
#include <Components/RigidBody.h>
#include <Components/Sprite.h>
#include <Engine/EngineBravo.h>
#include <GameObject.h>
#include <Global/FSConverter.h>

class ECCoinPrefab
{
public:
	ECCoinPrefab();
	GameObject* createECCoinPrefab(GameObject& objDroppingCoin);

private:
	float mCoinWidth;
	float mCoinHeight;
	Vector2 mCoinSpritePosition;
	SpriteDef mCoinSpriteDef;

	void addSprite(GameObject* gameObject);
	void addRigidBody(GameObject* gameObject);
	void addCollider(GameObject* gameObject);
	void setTransform(GameObject* gameObject, Transform objDroppingCoinTransform);
};
