#pragma once
#include "GameObject.h"
#include "Network/INetworkPrefab.h"

class EnemyPrefab : public INetworkPrefab
{
public:
	EnemyPrefab();
	GameObject* createEnemyPrefab() override;
	int getPrefabID() const override;

private:
	void setTransform(GameObject* gameObject);
	void addSprite(GameObject* gameObject);
	void addRigidBody(GameObject* gameObject);
	void addCollider(GameObject* gameObject);
	static void addAnimations(GameObject* gameObject);

private:
};