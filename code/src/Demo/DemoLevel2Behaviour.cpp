#include "DemoLevel2Behaviour.h"

#include <Animation.h>
#include <EnemyBehaviourScript.h>
#include <EngineBravo.h>
#include <Input.h>
#include <RigidBody.h>
#include <cmath>

void DemoLevel2Behaviour::onStart()
{
	mGameObject->setTag("DemoLevel2");

	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = &scene.getGameObjectsWithTag("EnemyMoving")[0].get();
	if (enemy != nullptr)
	{
		mInitialY = enemy->getTransform().position.y;
		if (enemy->hasComponent<RigidBody>())
		{
			enemy->getComponents<RigidBody>()[0].get().setActive(false);
		}
	}

	GameObject* enemyStatic = &scene.getGameObjectsWithTag("EnemyStatic")[0].get();
	RigidBody* rigidBody = new RigidBody();

	rigidBody->setCanRotate(true);
	rigidBody->setIsMoveableByForce(true);
	rigidBody->setDensity(1.0f);
	rigidBody->setFriction(0.0f);
	rigidBody->setRestitution(0.0f);
	rigidBody->setGravityScale(0.0f);
	rigidBody->setMass(5.0f);
	rigidBody->setLinearDamping(0.3f);
	rigidBody->setAngularDamping(0.3f);

	enemyStatic->addComponent(rigidBody);

	BoxCollider* boxCollider = new BoxCollider();
	// boxCollider->setTrigger(true);
	boxCollider->setWidth(20);
	boxCollider->setHeight(20);

	enemyStatic->addComponent(boxCollider);

	if (enemyStatic != nullptr)
	{
		if (enemyStatic->hasComponent<EnemyBehaviourScript>())
		{
			enemyStatic->getComponents<EnemyBehaviourScript>()[0].get().deactivateAllAnimations();
			if (enemy->hasComponent<RigidBody>())
			{
				enemy->getComponents<RigidBody>()[0].get().setActive(false);
			}
		}
	}

	GameObject* enemyWithPathfinding = &scene.getGameObjectsWithTag("EnemyWithPathfinding")[0].get();
	if (enemyWithPathfinding != nullptr)
	{
		if (enemyWithPathfinding->hasComponent<RigidBody>())
		{
			enemyWithPathfinding->getComponents<RigidBody>()[0].get().setActive(true);
		}
	}
}

void DemoLevel2Behaviour::onUpdate()
{
	moveWithPathfinding();
	moveEnemy();
	rotateEnemy();
	scaleEnemy();
}

void DemoLevel2Behaviour::onCollide(GameObject* aGameObject) {}

void DemoLevel2Behaviour::moveEnemy()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();
	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_8))
	{
		Time::timeDilation = Time::timeDilation + 0.1f;
	}

	if (input.GetKeyDown(Key::Key_9))
	{
		Time::timeDilation = Time::timeDilation - 0.1f;
	}

	GameObject* enemy = &scene.getGameObjectsWithTag("EnemyMoving")[0].get();
	if (enemy == nullptr)
	{
		std::cout << "Enemy not found" << std::endl;
		return;
	}

	Transform transform = enemy->getTransform();

	if (mMovingUp)
	{
		transform.position.y += 10.0f * Time::deltaTime;
		if (transform.position.y >= mInitialY + 20.0f)
		{
			mMovingUp = false;
		}
	}
	else
	{
		transform.position.y -= 10.0f * Time::deltaTime;
		if (transform.position.y <= mInitialY - 20.0f)
		{
			mMovingUp = true;
		}
	}
	enemy->getComponentsWithTag<Animation>("enemyWalking")[0].get().setActive(true);
	enemy->getComponentsWithTag<Sprite>("idleSprite")[0].get().setActive(false);

	enemy->setTransform(transform);
}

void DemoLevel2Behaviour::scaleEnemy()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = &scene.getGameObjectsWithTag("EnemyStatic")[0].get();
	if (enemy == nullptr)
	{
		std::cout << "Enemy not found" << std::endl;
		return;
	}

	Transform transform = enemy->getTransform();
	static bool scalingUp = true;

	if (scalingUp)
	{
		transform.scale.x += 0.01f;
		transform.scale.y += 0.01f;
		if (transform.scale.x >= 1.5f)
		{
			scalingUp = false;
		}
	}
	else
	{
		transform.scale.x -= 0.01f;
		transform.scale.y -= 0.01f;
		if (transform.scale.x <= 0.5f)
		{
			scalingUp = true;
		}
	}

	enemy->setTransform(transform);
}

void DemoLevel2Behaviour::rotateEnemy()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = &scene.getGameObjectsWithTag("EnemyStatic")[0].get();
	if (enemy == nullptr)
	{
		std::cout << "Enemy not found" << std::endl;
		return;
	}
	Transform transform = enemy->getTransform();
	// enemy->getComponents<RigidBody>()[0].get().addTorque(100.0f * Time::deltaTime);
	// transform.rotate(100.0f * Time::deltaTime);
	enemy->setTransform(transform);
}

void DemoLevel2Behaviour::moveWithPathfinding()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = &scene.getGameObjectsWithTag("EnemyWithPathfinding")[0].get();
	if (enemy == nullptr)
	{
		std::cout << "Enemy not found" << std::endl;
		return;
	}

	if (enemy->hasComponent<EnemyBehaviourScript>())
	{
		enemy->getComponents<EnemyBehaviourScript>()[0].get().moveWithPathfinding();
	}
	else
	{
		std::cout << "Enemy does not have EnemyBehaviourScript" << std::endl;
	}
}
