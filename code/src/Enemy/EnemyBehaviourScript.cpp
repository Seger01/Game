#include "EnemyBehaviourScript.h"
#include "BSCoinPrefab.h"
#include "BulletBehaviourScript.h"
#include "ECCoinPrefab.h"
#include <Animation.h>
#include <EngineBravo.h>
#include <GameObject.h>
#include <Input.h>
#include <RigidBody.h>
#include <SceneManager.h>
#include <Sprite.h>
#include <Time.h>
#include <functional>
#include <iostream>
#include <chrono>
#include <thread>


EnemyBehaviourScript::EnemyBehaviourScript(float aHealth) : mHealth(aHealth) {}

EnemyBehaviourScript::EnemyBehaviourScript(const EnemyBehaviourScript& other)
	: mHealth(other.mHealth), mIsDead(other.mIsDead), mMapWidth(other.mMapWidth), mMapHeight(other.mMapHeight),
	  mCurrentPathIndex(other.mCurrentPathIndex), mPathUpdateTime(other.mPathUpdateTime),
	  mPreviousPlayerPosition(other.mPreviousPlayerPosition)
{
	if (other.mPathfinding)
	{
		mPathfinding = std::make_unique<Pathfinding>(*other.mPathfinding);
	}
}

void EnemyBehaviourScript::onStart()
{
	mIsDead = false;
	mPreviousPlayerPosition = Vector2(0, 0);
	mPathMarkerSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{289, 320, 16, 16}, 16, 16};
	mGraphNodeSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{288, 369, 15, 14}, 15, 14};
}

void EnemyBehaviourScript::onUpdate()
{
	if (mPathfinding == nullptr)
	{
		return;
	}

	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_V))
	{
		drawPath = !drawPath;
	}

	if (input.GetKeyDown(Key::Key_G))
	{
		drawGraph = !drawGraph;
	}

	if (drawPath)
	{
		visualizePath(mPath);
	}
	else
	{
		removePathVisualization();
	}

	if (drawGraph)
	{
		visualizeGraph();
	}
	else
	{
		removeGraphVisualization();
	}
}

void EnemyBehaviourScript::onCollide(GameObject* aGameObject)
{
	if (mIsDead)
	{
		return;
	}

	if (aGameObject->getTag() == "Bullet")
	{
		BulletBehaviourScript& bullet = aGameObject->getComponents<BulletBehaviourScript>().at(0);
		takeDamage(bullet.getDamage());
		setGlowRed(true);

		// Reset the color after 0.5 seconds
        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
			if (!mIsDead) {
            	setGlowRed(false);
			}
        }).detach();
	}
}

void EnemyBehaviourScript::toggleAnimaionEnabled() {}

void EnemyBehaviourScript::setAnimationActive(std::string aAnimationTag, bool aState) {}

void EnemyBehaviourScript::deactivateAllAnimations()
{
	for (auto animation : mGameObject->getComponents<Animation>())
	{
		animation.get().setActive(false);
	}
}

void EnemyBehaviourScript::setFlipX(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (auto animation : mGameObject->getComponents<Animation>())
		{
			animation.get().setFlipX(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (auto sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.get().setFlipX(aState);
		}
	}
}

void EnemyBehaviourScript::setFlipY(bool aState)
{
	if (mGameObject->hasComponent<Animation>())
	{
		for (auto animation : mGameObject->getComponents<Animation>())
		{
			animation.get().setFlipY(aState);
		}
	}
	else if (mGameObject->hasComponent<Sprite>())
	{
		for (auto sprite : mGameObject->getComponents<Sprite>())
		{
			sprite.get().setFlipY(aState);
		}
	}
}

void EnemyBehaviourScript::takeDamage(float aDamage)
{
	if (mHealth <= 0)
	{
		onDeath();
	}
	else
	{
		mHealth -= aDamage;
	}
}

void EnemyBehaviourScript::onDeath()
{
	if (mIsDead)
	{
		return;
	}
	mIsDead = true;

	EngineBravo& engine = EngineBravo::getInstance();
	SceneManager& sceneManager = engine.getSceneManager();
	if (mGameObject != nullptr)
	{
		//  std::cout << "Creating Coins" << std::endl;
		// BSCoinPrefab coinPrefab;
		// GameObject* coin = coinPrefab.createBSCoinPrefab(*mGameObject);
		// sceneManager.getCurrentScene()->addGameObject(coin);

		//  ECCoinPrefab coinPrefab2;
		// GameObject* coin2 = coinPrefab2.createECCoinPrefab(*mGameObject);
		//  sceneManager.getCurrentScene()->addGameObject(coin2);

		std::cout << "Removing GameObject: " << mGameObject->getTag() << std::endl;
		sceneManager.getCurrentScene().requestGameObjectRemoval(mGameObject);
	}
	else
	{
		std::cerr << "Error: mGameObject is already null!" << std::endl;
	}
}

void EnemyBehaviourScript::setGlowRed(bool aState)
{
    if (mGameObject->hasComponent<Sprite>())
    {
        Sprite& sprite = mGameObject->getComponents<Sprite>()[0].get();
        if (aState)
        {
            sprite.setColorFilter(Color(255, 0, 0, 255)); // Set color to red
        }
        else
        {
            sprite.setColorFilter(Color(255, 255, 255, 255)); // Reset to original color
        }
    }
}

int EnemyBehaviourScript::getGridPosition(const Vector2& position) const
{
	int gridX = static_cast<int>(position.x) / 16;
	int gridY = static_cast<int>(position.y) / 16;

	// Ensure gridX and gridY are within valid bounds
	if (gridX < 0 || gridX >= mMapWidth || gridY < 0 || gridY >= mMapHeight)
	{
		return -1; // Return an invalid position
	}

	int gridPosition = gridY * mMapWidth + gridX;

	return gridPosition;
}

bool EnemyBehaviourScript::isValidPosition(int position) const
{
	return mPathfinding->getAdjacencyList().find(position) != mPathfinding->getAdjacencyList().end();
}

float EnemyBehaviourScript::vectorLength(const Vector2& vec) { return std::sqrt(vec.x * vec.x + vec.y * vec.y); }

Vector2 EnemyBehaviourScript::normalizeVector(const Vector2& vec)
{
	float length = vectorLength(vec);
	if (length != 0)
	{
		return Vector2(vec.x / length, vec.y / length);
	}
	return vec;
}

void EnemyBehaviourScript::visualizePath(const std::vector<int>& path)
{
	removePathVisualization();
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	// Create new path visualization
	for (int position : path)
	{
		int x = position % mMapWidth;
		int y = position / mMapWidth;

		GameObject* marker = new GameObject();
		marker->setTag("PathMarker");
		Transform transform;
		transform.position = Vector2(x * 16, y * 16);
		marker->setTransform(transform);

		Sprite* sprite = engine.getResourceManager().createSprite(mPathMarkerSpriteDef);
		sprite->setLayer(2);
		marker->addComponent(sprite);

		scene.addGameObject(marker);
	}
}

void EnemyBehaviourScript::removePathVisualization()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	std::vector<std::reference_wrapper<GameObject>> pathMarkers = scene.getGameObjectsWithTag("PathMarker");
	for (GameObject& marker : pathMarkers)
	{
		scene.requestGameObjectRemoval(&marker);
	}
}

void EnemyBehaviourScript::visualizeGraph()
{
	removeGraphVisualization();
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	for (auto node : mPathfinding->getAdjacencyList())
	{
		int position = node.first;
		int x = position % mMapWidth;
		int y = position / mMapWidth;

		GameObject* marker = new GameObject();
		marker->setTag("GraphNode");
		Transform transform;
		transform.position = Vector2(x * 16, y * 16);
		marker->setTransform(transform);

		Sprite* sprite = engine.getResourceManager().createSprite(mGraphNodeSpriteDef);
		sprite->setLayer(7);
		marker->addComponent(sprite);

		scene.addGameObject(marker);
	}
}

void EnemyBehaviourScript::removeGraphVisualization()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();

	std::vector<std::reference_wrapper<GameObject>> graphNodes = scene.getGameObjectsWithTag("GraphNode");
	for (GameObject& marker : graphNodes)
	{
		scene.requestGameObjectRemoval(&marker);
	}
}

void EnemyBehaviourScript::moveWithPathfinding()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene& scene = engine.getSceneManager().getCurrentScene();
	GameObject* enemy = mGameObject;
	if (enemy == nullptr)
	{
		return;
	}
	GameObject& player = scene.getGameObjectsWithTag("Player")[0];
	Vector2 playerPosition = player.getTransform().position;
	int enemyPosition = getGridPosition(enemy->getTransform().position);
	int playerGridPosition = getGridPosition(playerPosition);
	if (enemyPosition == -1 || playerGridPosition == -1 || !isValidPosition(enemyPosition) ||
		!isValidPosition(playerGridPosition))
	{
		return;
	}

	// Recalculate path if the player has moved significantly or after a certain time interval
	float distanceToPreviousPosition = vectorLength(playerPosition - mPreviousPlayerPosition);
	mPathUpdateTime += Time::deltaTime;
	if (distanceToPreviousPosition > 16.0f || mPathUpdateTime > 1.0f)
	{
		mPath = mPathfinding->findPath(enemyPosition, playerGridPosition);
		mCurrentPathIndex = 0;
		mPreviousPlayerPosition = playerPosition;
		mPathUpdateTime = 0.0f;
	}
	if (!mPath.empty() && mCurrentPathIndex < mPath.size() - 1)
	{
		int nextPosition = mPath[mCurrentPathIndex + 1];
		if (!isValidPosition(nextPosition))
		{
			return;
		}
		int nextX = nextPosition % mMapWidth;
		int nextY = nextPosition / mMapWidth;
		Transform transform = enemy->getTransform();
		Vector2 currentPosition = transform.position;
		Vector2 targetPosition(nextX * 16, nextY * 16);
		Vector2 direction = targetPosition - currentPosition;
		direction = normalizeVector(direction);
		float speed = 1000.0f * Time::deltaTime;
		Vector2 movement = direction * speed * Time::deltaTime;
		if (vectorLength(targetPosition - currentPosition) <= vectorLength(movement))
		{
			transform.position = targetPosition;
			mCurrentPathIndex++;
		}
		else
		{
			transform.position += movement;
		}
		enemy->setTransform(transform);
	}
}

void EnemyBehaviourScript::setPathfinding(std::unique_ptr<Pathfinding>&& aPathfinding)
{
	mPathfinding = std::move(aPathfinding);
}

void EnemyBehaviourScript::setMapWidth(int aMapWidth) { mMapWidth = aMapWidth; }

void EnemyBehaviourScript::setMapHeight(int aMapHeight) { mMapHeight = aMapHeight; }

int EnemyBehaviourScript::getMapWidth() const { return mMapWidth; }

int EnemyBehaviourScript::getMapHeight() const { return mMapHeight; }

std::unique_ptr<Pathfinding> EnemyBehaviourScript::getPathfinding() const
{
	return std::make_unique<Pathfinding>(*mPathfinding);
}
