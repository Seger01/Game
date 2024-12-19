#include "PlayerBehaviourScript.h"

#include <iostream>

#include "BulletBehaviourScript.h"
#include "BulletPrefab.h"
#include "Controller.h"
#include <Animation.h>
#include <EngineBravo.h>
#include <GameObject.h>
#include <Input.h>
#include <InputStructs.h>
#include <Network/NetworkObject.h>
#include <ParticleEmitter.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <SpriteDefUtil.h>

std::string PlayerBehaviourScript::currentActiveAnimationTag()
{
	for (Animation& animation : mGameObject->getComponents<Animation>())
	{
		if (animation.isActive())
		{
			return animation.getTag();
		}
	}
	return "";
}

void PlayerBehaviourScript::setFlipX(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (Animation& animation : mGameObject->getComponents<Animation>())
		{
			animation.setFlipX(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (Sprite& sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.setFlipX(aState);
		}
	}
}

void PlayerBehaviourScript::setFlipY(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (Animation& animation : mGameObject->getComponents<Animation>())
		{
			animation.setFlipY(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (Sprite& sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.setFlipY(aState);
		}
	}
}

void PlayerBehaviourScript::deactivateAllAnimations()
{
	for (Animation& animation : mGameObject->getComponents<Animation>())
	{
		animation.setActive(false);
	}
}

void PlayerBehaviourScript::setAnimationActive(std::string aAnimationTag, bool aState)
{
	for (Animation& animation : mGameObject->getComponents<Animation>())
	{
		if (animation.getTag() == aAnimationTag)
		{
			animation.setActive(aState);
		}
	}
}

void PlayerBehaviourScript::onStart() {}

void PlayerBehaviourScript::handleAnimations()
{
	if (mGameObject->hasComponent<NetworkObject>())
	{
		NetworkObject& networkObject = mGameObject->getComponents<NetworkObject>().at(0);
		if (!networkObject.isOwner())
		{
			return;
		}
	}

	Vector2 currentVelocity;
	if (mGameObject->hasComponent<RigidBody>())
	{
		currentVelocity = mGameObject->getComponents<RigidBody>()[0].get().getLinearVelocity();
	}
	else
	{
		return;
	}

	if (abs(currentVelocity.x) < 0.1 && abs(currentVelocity.y) < 0.1)
	{
		if ((currentActiveAnimationTag() == "playerIdleFront") || (currentActiveAnimationTag() == "playerIdleBack") ||
			(currentActiveAnimationTag() == "playerIdleSide"))
		{
		}
		else
		{
			if (currentActiveAnimationTag() == "playerWalkingFront")
			{
				deactivateAllAnimations();
				setAnimationActive("playerIdleFront", true);
			}
			else if (currentActiveAnimationTag() == "playerWalkingBack")
			{
				deactivateAllAnimations();
				setAnimationActive("playerIdleBack", true);
			}
			else if (currentActiveAnimationTag() == "playerWalkingFrontSide")
			{
				deactivateAllAnimations();
				setAnimationActive("playerIdleSide", true);
			}
			else if (currentActiveAnimationTag() == "playerWalkingBackSide")
			{
				deactivateAllAnimations();
				setAnimationActive("playerIdleBack", true);
			}
			else
			{
				deactivateAllAnimations();
				setAnimationActive("playerIdleBack", true);
			}
		}

		if (currentVelocity.x > 0)
		{
			setFlipX(true);
		}
		else if (currentVelocity.x < 0)
		{
			setFlipX(false);
		}
	}
	else
	{
		if (currentVelocity.y < 0)
		{
			if (abs(currentVelocity.x) > 5)
			{
				deactivateAllAnimations();
				setAnimationActive("playerWalkingBackSide", true);
			}
			else if (abs(currentVelocity.x) < 5)
			{
				deactivateAllAnimations();
				setAnimationActive("playerWalkingBack", true);
			}
		}
		else
		{
			if (abs(currentVelocity.x) > 5)
			{
				deactivateAllAnimations();
				setAnimationActive("playerWalkingFrontSide", true);
			}
			else if (abs(currentVelocity.x) < 5)
			{
				deactivateAllAnimations();
				setAnimationActive("playerWalkingFront", true);
			}
		}

		if ((currentVelocity.x) < -5)
		{
			setFlipX(false);
		}
		else if ((currentVelocity.x) > 5)
		{
			setFlipX(true);
		}
	}
}

void PlayerBehaviourScript::handleMovement()
{
	static const float movementSpeed = 160000.0f;

	if (mGameObject->hasComponent<NetworkObject>())
	{
		NetworkObject& networkObject = mGameObject->getComponents<NetworkObject>().at(0);
		if (!networkObject.isOwner())
		{
			return;
		}
	}

	Input& input = Input::getInstance();
	static Controller controller(0);

	controller.update();

	if (controller.isConnected())
	{
		if (controller.getLeftStickUp() > 0)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(
				Vector2(0, -(movementSpeed * controller.getLeftStickUp()) * Time::deltaTime));
		}
		if (controller.getLeftStickLeft() > 0)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(
				Vector2(-(movementSpeed * controller.getLeftStickLeft()) * Time::deltaTime, 0));
		}
		if (controller.getLeftStickDown() > 0)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(
				Vector2(0, (movementSpeed * controller.getLeftStickDown()) * Time::deltaTime));
		}
		if (controller.getLeftStickRight() > 0)
		{
			mGameObject->getComponents<RigidBody>()[0].get().addForce(
				Vector2((movementSpeed * controller.getLeftStickRight()) * Time::deltaTime, 0));
		}

		// controller.print();

		if (controller.isButton(Key::Controller_R1))
		{
			if (controller.getRightStickUp() == 0 && controller.getRightStickLeft() == 0 &&
				controller.getRightStickDown() == 0 && controller.getRightStickRight() == 0)
			{
				return;
			}

			// Create and setup the bullet
			GameObject* bulletObject = BulletPrefabFactory().createBulletPrefab(*this->mGameObject);

			// Set bullet's initial position
			bulletObject->getTransformRef().position = mGameObject->getTransform().position;

			// Add force to bullet
			RigidBody& bulletRigidBody = bulletObject->getComponents<RigidBody>()[0];
			float bulletSpeed = 16000.0f;
			Vector2 direction = {-controller.getRightStickLeft() + controller.getRightStickRight(),
								 -controller.getRightStickUp() + controller.getRightStickDown()};

			bulletRigidBody.addForce(direction * bulletSpeed);

			EngineBravo::getInstance().getSceneManager().getCurrentScene().addGameObject(bulletObject);
		}
	}

	// controller.print();

	Transform parentTransform = this->mGameObject->getTransform();

	if (input.GetKey(Key::Key_E))
	{
		deactivateAllAnimations();
	}

	if (input.GetKey(Key::Key_R))
	{
		parentTransform.rotate(1.0f);
	}
	if (input.GetKey(Key::Key_T))
	{
		parentTransform.rotate(-1.0f);
	}

	if (input.GetKey(Key::Key_W))
	{
		mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(0, -movementSpeed * Time::deltaTime));
	}
	if (input.GetKey(Key::Key_A))
	{
		mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(-movementSpeed * Time::deltaTime, 0));
	}
	if (input.GetKey(Key::Key_S))
	{
		mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(0, movementSpeed * Time::deltaTime));
	}
	if (input.GetKey(Key::Key_D))
	{
		mGameObject->getComponents<RigidBody>()[0].get().addForce(Vector2(movementSpeed * Time::deltaTime, 0));
	}
	if (input.GetKey(Key::Key_1))
	{
		parentTransform.scale = Vector2(2.3, 2.3);
	}
	if (input.GetKey(Key::Key_2))
	{
		parentTransform.scale = Vector2(0.5, 0.5);
	}
	if (input.GetKey(Key::Key_3))
	{
		parentTransform.scale = Vector2(1.0, 1.0);
	}
	this->mGameObject->setTransform(parentTransform);
}

void PlayerBehaviourScript::hanldeCameraMovement()
{
	if (mGameObject->hasComponent<NetworkObject>())
	{
		NetworkObject& networkObject = mGameObject->getComponents<NetworkObject>().at(0);
		if (!networkObject.isOwner())
		{
			return;
		}
	}

	Camera* currentCam = EngineBravo::getInstance().getSceneManager().getCurrentScene().getCameraWithTag("MainCamera");

	if (!currentCam->hasParent())
	{
		currentCam->setParent(*mGameObject);
		currentCam->setTransform(Transform(Vector2(0, 0)));
	}

	// Transform playerTransform = this->mGameObject->getTransform();
	//
	// currentCam->setTransform(playerTransform);

	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_M))
	{
		currentCam->startShake(0.5f, 2.0f);
	}
}

void PlayerBehaviourScript::handleAspectRatioTest()
{
	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_I))
	{
		EngineBravo& engine = EngineBravo::getInstance();
		engine.getRenderSystem().setAspectRatio(Point(16, 9));
	}
	if (input.GetKeyDown(Key::Key_O))
	{
		EngineBravo& engine = EngineBravo::getInstance();
		engine.getRenderSystem().setAspectRatio(Point(1, 1));
	}
}

void PlayerBehaviourScript::fireBullet(Point mousePosition)
{
	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();

	// Get the camera
	Camera* currentCam = sceneManager.getCurrentScene().getCameraWithTag("MainCamera");
	Vector2 cameraOrigin = currentCam->getOrigin();

	// Get window dimensions
	int windowWidth = EngineBravo::getInstance().getRenderSystem().getWindow().getSize().x;
	int windowHeight = EngineBravo::getInstance().getRenderSystem().getWindow().getSize().y;

	// Convert mouse position to Vector2 and calculate relative to screen center
	Vector2 mousePositionVector(mousePosition.x, mousePosition.y);

	// Transform to world space, accounting for camera position and window dimensions
	Vector2 worldMousePosition =
		cameraOrigin + Vector2(mousePositionVector.x * (currentCam->getWidth() / static_cast<float>(windowWidth)),
							   mousePositionVector.y * (currentCam->getHeight() / static_cast<float>(windowHeight)));

	// Get player position and calculate direction
	Vector2 playerPosition = this->mGameObject->getTransform().position;
	Vector2 direction = worldMousePosition - playerPosition;

// Debug output
#ifdef DEBUG_SHOOTING
	std::cout << "Mouse Position: " << mousePositionVector.x << ", " << mousePositionVector.y << std::endl;
	std::cout << "Camera Origin: " << cameraOrigin.x << ", " << cameraOrigin.y << std::endl;
	std::cout << "World Mouse: " << worldMousePosition.x << ", " << worldMousePosition.y << std::endl;
	std::cout << "Player Position: " << playerPosition.x << ", " << playerPosition.y << std::endl;
	std::cout << "Pre-normalized Direction: " << direction.x << ", " << direction.y << std::endl;
#endif

	// Normalize the direction vector
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 0.0001f)
	{
		direction.x /= length;
		direction.y /= length;
	}

	// Create bullet slightly offset from player position in the firing direction
	Vector2 spawnOffset = direction * 20.0f;
	Vector2 bulletSpawnPosition = playerPosition + spawnOffset;

	// Create and setup the bullet
	GameObject* bulletObject = BulletPrefabFactory().createBulletPrefab(*this->mGameObject);

	// Set bullet's initial position
	bulletObject->getTransform().position = bulletSpawnPosition;

	// Add force to bullet
	RigidBody& bulletRigidBody = bulletObject->getComponents<RigidBody>()[0];
	float bulletSpeed = 16000.0f;
	bulletRigidBody.addForce(direction * bulletSpeed);

	sceneManager.getCurrentScene().addGameObject(bulletObject);
}

void PlayerBehaviourScript::onUpdate()
{
	Input& input = Input::getInstance();

	handleMovement();
	handleAnimations();
	handleAspectRatioTest();

	hanldeCameraMovement();

	if (input.GetKeyDown(Key::Key_C))
	{
		Camera* mainCam = EngineBravo::getInstance().getSceneManager().getCurrentScene().getCameraWithTag("MainCamera");

		mainCam->getDebugOverlayRef().renderColliders = !mainCam->getDebugOverlayRef().renderColliders;
	}

	if (input.GetKeyDown(Key::Key_F))
	{
		Camera* mainCam = EngineBravo::getInstance().getSceneManager().getCurrentScene().getCameraWithTag("MainCamera");

		mainCam->getDebugOverlayRef().showFPS = !mainCam->getDebugOverlayRef().showFPS;
	}

	if (input.GetMouseButtonDown(MouseButton::LEFT))
	{
		fireBullet(input.MousePosition());
	}

	if (mGameObject->hasComponent<ParticleEmitter>())
	{
		static bool emitterMode = false;

		ParticleEmitter& emitter = mGameObject->getComponents<ParticleEmitter>()[0];

		if (input.GetKeyDown(Key::Key_P))
		{
			emitter.setActive(!emitter.isActive());
		}

		if (input.GetKeyDown(Key::Key_Space))
		{
			emitterMode = !emitterMode;
		}

		if (emitterMode)
		{
			emitter.setAngle(0, 45);
			emitter.getRelativeTransform().rotation += 1.0f * Time::deltaTime;
		}
		else
		{
			emitter.setAngle(0, 360);
			emitter.getRelativeTransform().rotation = 0.0f;
		}
	}
}

void PlayerBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (aGameObject != nullptr)
	{
		// std::cout << "Player collided with " << aGameObject->getName() <<
		// std::endl;
	}
}

float PlayerBehaviourScript::getHealth() { return mHealth; }

float PlayerBehaviourScript::getMaxHealth() { return mMaxHealth; }

int PlayerBehaviourScript::getECCount() { return mECCount; }

int PlayerBehaviourScript::getBSCount() { return mBSCount; }

void PlayerBehaviourScript::setHealth(float aHealth) { mHealth = aHealth; }

void PlayerBehaviourScript::setMaxHealth(float aMaxHealth) { mMaxHealth = aMaxHealth; }

void PlayerBehaviourScript::setECCount(int aECCount) { mECCount = aECCount; }

void PlayerBehaviourScript::setBSCount(int aBSCount) { mBSCount = aBSCount; }
