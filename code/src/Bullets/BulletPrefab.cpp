#include "BulletPrefab.h"
#include "Particle.h"
#include "ParticleEmitter.h"

BulletPrefabFactory::BulletPrefabFactory()
{
	mBulletWidth = 12;
	mBulletHeight = 12;
	mBulletSpritePosition = {322, 320};

	FSConverter fsConverter;
	std::string bulletSpritePath = fsConverter.getResourcePath("enterthegungeon_bullets.png");
	mBulletSpriteDef = {bulletSpritePath,
						Rect{mBulletSpritePosition.x, mBulletSpritePosition.y, static_cast<int>(mBulletWidth),
							 static_cast<int>(mBulletHeight)},
						mBulletWidth, mBulletHeight};
}

GameObject* BulletPrefabFactory::createBulletPrefab(GameObject& shooter)
{
	GameObject* bulletPrefab = new GameObject;
	bulletPrefab->setName("Bullet");
	bulletPrefab->setTag("Bullet");
	float damage = 20.0f;
	bulletPrefab->addComponent<BulletBehaviourScript>(damage);
	setTransform(bulletPrefab, shooter.getTransform());
	addSprite(bulletPrefab);
	addRigidBody(bulletPrefab);
	addCollider(bulletPrefab);
	addParticleEmitter(bulletPrefab);

	return bulletPrefab;
}

void BulletPrefabFactory::setTransform(GameObject* gameObject, Transform shooterTransform)
{
	Transform objectTransform;
	objectTransform.position.x = shooterTransform.position.x;
	objectTransform.position.y = shooterTransform.position.y;
	gameObject->setTransform(objectTransform);
}

void BulletPrefabFactory::addSprite(GameObject* gameObject)
{
	Sprite* bulletSprite = EngineBravo::getInstance().getResourceManager().createSprite(mBulletSpriteDef);
	bulletSprite->setRelativePosition(Transform(Vector2(-6, -6)));
	bulletSprite->setLayer(3);
	gameObject->addComponent(bulletSprite);
}

void BulletPrefabFactory::addRigidBody(GameObject* gameObject)
{
	RigidBody* rigidBody = new RigidBody();

	rigidBody->setCanRotate(true);
	rigidBody->setHasGravity(false);
	rigidBody->setIsMoveableByForce(true);
	rigidBody->setDensity(1.0f);
	rigidBody->setFriction(5.0f);
	rigidBody->setRestitution(0.0f);
	rigidBody->setGravityScale(0.0f);
	rigidBody->setMass(0.0f);
	rigidBody->setLinearDamping(0.0f);
	rigidBody->setAngularDamping(0.0f);

	gameObject->addComponent(rigidBody);
}

void BulletPrefabFactory::addCollider(GameObject* gameObject)
{
	// BoxCollider* boxCollider = new BoxCollider();
	// boxCollider->setWidth(mBulletWidth);
	// boxCollider->setHeight(mBulletHeight);
	// boxCollider->setTrigger(true);
	CircleCollider* circleCollider = new CircleCollider();
	circleCollider->setRadius(mBulletWidth / 2);
	circleCollider->setIsTrigger(true);

	gameObject->addComponent(circleCollider);
}

void BulletPrefabFactory::addParticleEmitter(GameObject* gameObject)
{
	std::vector<Color> colorGradient = {
		Color(255, 255, 255, 255), // White
		Color(200, 200, 200, 255), // Light Gray
		Color(150, 150, 150, 255)  // Darker Gray
	};
	EmitterMode emitterMode = EmitterMode::Continuous;
	float speed = 2.0f;
	float acceleration = 0.0f;
	int minLifeTimeMs = 200;
	int maxLifeTimeMs = 1000;
	Vector2 startSize = Vector2(2, 2);
	Vector2 endSize = Vector2(0, 0);
	float rotation = 0.0f;
	float rotationSpeed = 0.0f;
	float rotationAcceleration = 0.0f;

	ParticleEmitter* emitter =
		new ParticleEmitter(emitterMode, speed, acceleration, minLifeTimeMs, maxLifeTimeMs, startSize, endSize,
							colorGradient, rotation, rotationSpeed, rotationAcceleration);
	emitter->setParticlesPerSecond(50);
	emitter->setAngle(0, 360);
	emitter->setLayer(4);
	emitter->setRelativeTransform(Transform(Vector2(0, 0)));
	Transform transform;
	// transform.position = Vector2(6, 6);
	emitter->setRelativeTransform(transform);
	emitter->setActive(true);

	gameObject->addComponent(emitter);
}
