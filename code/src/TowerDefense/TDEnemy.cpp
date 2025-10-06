#include "TowerDefense/TDEnemy.h"
#include "Engine/EngineBravo.h"
#include "Global/Time.h"
#include "Rendering/Sprite.h"
#include "ResourceManager/ResourceManager.h"
#include <cmath>

TDEnemy::TDEnemy(float health, float speed, int reward, const std::vector<Waypoint>& path)
    : mHealth(health), mMaxHealth(health), mSpeed(speed), mReward(reward), 
      mPath(path), mCurrentWaypointIndex(0), mReachedEnd(false) {}

void TDEnemy::onStart() {
    mGameObject->setTag("Enemy");
    
    // Add visual representation
    EngineBravo& engine = EngineBravo::getInstance();
    SpriteDef enemySprite = {"DinoSprites.png", Rect(4, 3, 15, 17), 15, 17};
    Sprite* sprite = engine.getResourceManager().createSprite(enemySprite);
    sprite->setLayer(2);
    mGameObject->addComponent(sprite);
}

void TDEnemy::onUpdate() {
    if (!isDead() && !mReachedEnd) {
        moveAlongPath();
    }
}

void TDEnemy::onCollide(GameObject* aGameObject) {
    if (aGameObject->getTag() == "Projectile") {
        takeDamage(10.0f);
    }
}

void TDEnemy::moveAlongPath() {
    if (mCurrentWaypointIndex >= mPath.size()) {
        mReachedEnd = true;
        return;
    }
    
    Transform& transform = mGameObject->getTransformRef();
    const Waypoint& target = mPath[mCurrentWaypointIndex];
    
    float dx = target.x - transform.position.x;
    float dy = target.y - transform.position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance < 5.0f) {
        mCurrentWaypointIndex++;
        return;
    }
    
    // Normalize direction and move
    float dirX = dx / distance;
    float dirY = dy / distance;
    
    transform.position.x += dirX * mSpeed * Time::deltaTime;
    transform.position.y += dirY * mSpeed * Time::deltaTime;
}

void TDEnemy::takeDamage(float damage) {
    mHealth -= damage;
    if (mHealth <= 0) {
        die();
    }
}

void TDEnemy::die() {
    if (mGameObject) {
        mGameObject->setActive(false);
    }
}
