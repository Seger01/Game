#include "BulletBehaviourScript.h"
#include "BulletDestroyParticleBehaviourScript.h"
#include <Global/Time.h>

BulletBehaviourScript::BulletBehaviourScript(float damage)
	: mDamage(damage), mIsMarkedForRemoval(false), mParticleObject(nullptr)
{
}

void BulletBehaviourScript::onStart() {}

void BulletBehaviourScript::onUpdate() {}

void BulletBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (mIsMarkedForRemoval)
	{
		return;
	}

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	if (aGameObject->getTag() != "Player")
	{
		mIsMarkedForRemoval = true;
		if (mGameObject->hasComponent<RigidBody>())
		{
			mGameObject->getComponents<RigidBody>()[0].get().setActive(false);
		}

		// Create a new GameObject for the particle emitter
		mParticleObject = new GameObject;
		mParticleObject->setTag("BulletHitParticles");

		std::vector<Color> colorGradient = {
			Color(255, 0, 0, 255),	 // Red
			Color(255, 255, 0, 255), // Yellow
			Color(0, 255, 0, 255),	 // Green
			Color(0, 0, 255, 255)	 // Blue
		};

		EmitterMode emitterMode = EmitterMode::Burst;
		float speed = 100.0f;
		float acceleration = -100.0f;
		int minLifeTimeMs = 50;
		int maxLifeTimeMs = 150;
		Vector2 startSize = Vector2(5, 5);
		Vector2 endSize = Vector2(1, 1);
		float rotation = 0.0f;
		float rotationSpeed = 0.0f;
		float rotationAcceleration = 0.0f;

		ParticleEmitter* emitter =
			new ParticleEmitter(emitterMode, speed, acceleration, minLifeTimeMs, maxLifeTimeMs, startSize, endSize,
								colorGradient, rotation, rotationSpeed, rotationAcceleration);

		emitter->setParticlesPerSecond(200);
		emitter->setAngle(0, 360);
		emitter->setLayer(4);
		emitter->setTag("BulletParticles");
		Transform transform;
		transform.position = mGameObject->getTransform().position;
		mParticleObject->setTransform(transform);

		emitter->setRelativeTransform(transform);
		emitter->setActive(true);
		emitter->burst(200);

		mParticleObject->addComponent(emitter);
		mParticleObject->addComponent<BulletDestroyParticleBehaviourScript>();

		sceneManager.getCurrentScene().addGameObject(mParticleObject);

		sceneManager.getCurrentScene().requestGameObjectRemoval(mGameObject);
	}
}
