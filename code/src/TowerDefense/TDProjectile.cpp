#include "TowerDefense/TDProjectile.h"
#include "TowerDefense/TDEnemy.h"
#include "Global/Time.h"
#include <cmath>

TDProjectile::TDProjectile(GameObject* target, float damage, float speed)
    : mTarget(target), mDamage(damage), mSpeed(speed), mLifetime(0.0f) {}

void TDProjectile::onStart() {
    mGameObject->setTag("Projectile");
}

void TDProjectile::onUpdate() {
    mLifetime += Time::deltaTime;
    
    // Destroy projectile after 5 seconds
    if (mLifetime > 5.0f || mTarget == nullptr) {
        if (mGameObject) {
            mGameObject->setActive(false);
        }
        return;
    }
    
    // Move towards target
    Transform& myTransform = mGameObject->getTransformRef();
    Transform targetTransform = mTarget->getTransform();
    
    float dx = targetTransform.position.x - myTransform.position.x;
    float dy = targetTransform.position.y - myTransform.position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Check if we hit the target
    if (distance < 10.0f) {
        // Try to get the enemy component and deal damage
        auto enemyComponents = mTarget->getComponents<TDEnemy>();
        if (!enemyComponents.empty()) {
            enemyComponents[0].get().takeDamage(mDamage);
        }
        
        if (mGameObject) {
            mGameObject->setActive(false);
        }
        return;
    }
    
    // Move towards target
    if (distance > 0) {
        float dirX = dx / distance;
        float dirY = dy / distance;
        
        myTransform.position.x += dirX * mSpeed * Time::deltaTime;
        myTransform.position.y += dirY * mSpeed * Time::deltaTime;
    }
}

void TDProjectile::onCollide(GameObject* aGameObject) {
    if (aGameObject->getTag() == "Enemy") {
        // Damage is handled in onUpdate
        if (mGameObject) {
            mGameObject->setActive(false);
        }
    }
}
