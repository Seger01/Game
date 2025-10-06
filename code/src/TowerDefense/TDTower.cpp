#include "TowerDefense/TDTower.h"
#include "TowerDefense/TDProjectile.h"
#include "Engine/EngineBravo.h"
#include "Global/Time.h"
#include "Rendering/Sprite.h"
#include "ResourceManager/ResourceManager.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include <cmath>

TDTower::TDTower(TowerType type) 
    : mType(type), mTimeSinceLastShot(0.0f) {
    
    switch(type) {
        case TowerType::BASIC:
            mRange = 100.0f;
            mDamage = 10.0f;
            mFireRate = 1.0f;
            mCost = 100;
            break;
        case TowerType::RAPID:
            mRange = 80.0f;
            mDamage = 5.0f;
            mFireRate = 0.3f;
            mCost = 150;
            break;
        case TowerType::SNIPER:
            mRange = 200.0f;
            mDamage = 50.0f;
            mFireRate = 3.0f;
            mCost = 250;
            break;
        case TowerType::SPLASH:
            mRange = 90.0f;
            mDamage = 15.0f;
            mFireRate = 1.5f;
            mCost = 200;
            break;
    }
}

void TDTower::onStart() {
    mGameObject->setTag("Tower");
    
    // Add visual representation based on tower type
    EngineBravo& engine = EngineBravo::getInstance();
    SpriteDef towerSprite;
    
    switch(mType) {
        case TowerType::BASIC:
            // Blue tower
            towerSprite = {"enterthegungeon_bullets.png", Rect(0, 0, 16, 16), 16, 16};
            break;
        case TowerType::RAPID:
            // Red tower
            towerSprite = {"enterthegungeon_bullets.png", Rect(16, 0, 16, 16), 16, 16};
            break;
        case TowerType::SNIPER:
            // Yellow tower
            towerSprite = {"enterthegungeon_bullets.png", Rect(32, 0, 16, 16), 16, 16};
            break;
        case TowerType::SPLASH:
            // Green tower
            towerSprite = {"enterthegungeon_bullets.png", Rect(48, 0, 16, 16), 16, 16};
            break;
    }
    
    Sprite* sprite = engine.getResourceManager().createSprite(towerSprite);
    sprite->setLayer(1);
    mGameObject->addComponent(sprite);
}

void TDTower::onUpdate() {
    mTimeSinceLastShot += Time::deltaTime;
    
    if (mTimeSinceLastShot >= mFireRate) {
        findAndShootTarget();
    }
}

void TDTower::findAndShootTarget() {
    GameObject* target = findNearestEnemy();
    if (target != nullptr) {
        shootAt(target);
        mTimeSinceLastShot = 0.0f;
    }
}

GameObject* TDTower::findNearestEnemy() {
    Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
    std::vector<std::reference_wrapper<GameObject>> enemies = scene.getGameObjectsWithTag("Enemy");
    
    GameObject* nearest = nullptr;
    float minDistance = mRange;
    
    Transform& towerTransform = mGameObject->getTransformRef();
    
    for (auto& enemyRef : enemies) {
        GameObject& enemy = enemyRef.get();
        Transform enemyTransform = enemy.getTransform();
        
        float dx = enemyTransform.position.x - towerTransform.position.x;
        float dy = enemyTransform.position.y - towerTransform.position.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance < minDistance) {
            minDistance = distance;
            nearest = &enemy;
        }
    }
    
    return nearest;
}

void TDTower::shootAt(GameObject* target) {
    // Create a projectile
    GameObject* projectile = new GameObject();
    
    Transform& towerTransform = mGameObject->getTransformRef();
    Transform projectileTransform;
    projectileTransform.position = towerTransform.position;
    projectile->setTransform(projectileTransform);
    
    // Add projectile behavior component
    float projectileSpeed = 200.0f;
    projectile->addComponent<TDProjectile>(target, mDamage, projectileSpeed);
    
    EngineBravo::getInstance().getSceneManager().getCurrentScene().addGameObject(projectile);
}
