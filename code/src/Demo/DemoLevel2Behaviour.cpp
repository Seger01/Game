#include "DemoLevel2Behaviour.h"
#include <Animation.h>
#include <EnemyBehaviourScript.h>
#include <EngineBravo.h>
#include <Input.h>
#include <cmath>

void DemoLevel2Behaviour::onStart()
{
	mGameObject->setTag("DemoLevel2");

	EngineBravo& engine = EngineBravo::getInstance();
	Scene* scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
	if (enemy != nullptr)
	{
		mInitialY = enemy->getTransform().position.y;
		if (enemy->hasComponent<RigidBody>())
		{
			enemy->getComponents<RigidBody>()[0]->setActive(false);
		}
	}

	GameObject* enemyStatic = scene->getGameObjectsWithTag("EnemyStatic")[0];
	if (enemyStatic != nullptr)
	{
		if (enemyStatic->hasComponent<EnemyBehaviourScript>())
		{
			enemyStatic->getComponents<EnemyBehaviourScript>()[0]->deactivateAllAnimations();
			if (enemy->hasComponent<RigidBody>())
			{
				enemy->getComponents<RigidBody>()[0]->setActive(false);
			}
		}
	}

    GameObject* enemyWithPathfinding = scene->getGameObjectsWithTag("EnemyWithPathfinding")[0];
    if (enemyWithPathfinding != nullptr) {
        if (enemyWithPathfinding->hasComponent<RigidBody>()) {
            enemyWithPathfinding->getComponents<RigidBody>()[0]->setActive(true);
        }
    }

    mPreviousPlayerPosition = Vector2(0, 0);
}

void DemoLevel2Behaviour::onUpdate()
{
	moveWithPathfinding();
	moveEnemy();
	rotateEnemy();
}

void DemoLevel2Behaviour::onCollide(GameObject* aGameObject) {}

void DemoLevel2Behaviour::moveEnemy()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene* scene = engine.getSceneManager().getCurrentScene();
	Input& input = Input::getInstance();

	if (input.GetKeyDown(Key::Key_PageUp))
	{
		Time::timeDilation = Time::timeDilation + 0.1f;
	}

	if (input.GetKeyDown(Key::Key_PageDown))
	{
		Time::timeDilation = Time::timeDilation - 0.1f;
	}

	GameObject* enemy = scene->getGameObjectsWithTag("EnemyMoving")[0];
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
	enemy->getComponentsWithTag<Animation>("enemyWalking")[0]->setActive(true);
	enemy->getComponentsWithTag<Sprite>("idleSprite")[0]->setActive(false);

	enemy->setTransform(transform);
}

void DemoLevel2Behaviour::scaleEnemy()
{
	EngineBravo& engine = EngineBravo::getInstance();
	Scene* scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = scene->getGameObjectsWithTag("EnemyStatic")[0];
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
	Scene* scene = engine.getSceneManager().getCurrentScene();

	GameObject* enemy = scene->getGameObjectsWithTag("EnemyStatic")[0];
	if (enemy == nullptr)
	{
		std::cout << "Enemy not found" << std::endl;
		return;
	}
	Transform transform = enemy->getTransform();
	transform.rotate(100.0f * Time::deltaTime);
	enemy->setTransform(transform);
}

int DemoLevel2Behaviour::getGridPosition(const Vector2& position) const
{
	int x = static_cast<int>(position.x) / 16;
	int y = static_cast<int>(position.y) / 16;
	return y * mMapWidth + x;
}

bool DemoLevel2Behaviour::isValidPosition(int position) const {
    return mPathfinding->getAdjacencyList().find(position) != mPathfinding->getAdjacencyList().end();
}
float vectorLength(const Vector2& vec) { return std::sqrt(vec.x * vec.x + vec.y * vec.y); }

Vector2 normalizeVector(const Vector2& vec)
{
	float length = vectorLength(vec);
	if (length != 0)
	{
		return Vector2(vec.x / length, vec.y / length);
	}
	return vec;
}

void DemoLevel2Behaviour::moveWithPathfinding() {
    EngineBravo& engine = EngineBravo::getInstance();
    Scene* scene = engine.getSceneManager().getCurrentScene();

    GameObject* enemy = scene->getGameObjectsWithTag("EnemyWithPathfinding")[0];
    if (enemy == nullptr) {
        std::cout << "Enemy not found" << std::endl;
        return;
    }

    GameObject* player = scene->getGameObjectsWithTag("Player")[0];
    if (player == nullptr) {
        std::cout << "Player not found" << std::endl;
        return;
    }

    Vector2 playerPosition = player->getTransform().position;
    int enemyPosition = getGridPosition(enemy->getTransform().position);
    int playerGridPosition = getGridPosition(playerPosition);

    // Recalculate path if the player has moved significantly or after a certain time interval
    float distanceToPreviousPosition = vectorLength(playerPosition - mPreviousPlayerPosition);
    mPathUpdateTime += Time::deltaTime;

    if (distanceToPreviousPosition > 16.0f || mPathUpdateTime > 1.0f) {
        mPath = mPathfinding->findPath(enemyPosition, playerGridPosition);
        mCurrentPathIndex = 0;
        mPreviousPlayerPosition = playerPosition;
        mPathUpdateTime = 0.0f;
    }

    if (!mPath.empty() && mCurrentPathIndex < mPath.size() - 1) {
        int nextPosition = mPath[mCurrentPathIndex + 1];

        if (!isValidPosition(nextPosition)) {
            std::cout << "Next position is not valid on the graph" << std::endl;
            return;
        }

        int nextX = nextPosition % mMapWidth;
        int nextY = nextPosition / mMapWidth;

        Transform transform = enemy->getTransform();
        Vector2 currentPosition = transform.position;
        Vector2 targetPosition(nextX * 16, nextY * 16);

        Vector2 direction = targetPosition - currentPosition;
        direction = normalizeVector(direction);

        float speed = 25.0f;
        Vector2 movement = direction * speed * Time::deltaTime;

        if (vectorLength(targetPosition - currentPosition) <= vectorLength(movement)) {
            transform.position = targetPosition;
            mCurrentPathIndex++;
        } else {
            transform.position += movement;
        }

        enemy->setTransform(transform);
    }
}
