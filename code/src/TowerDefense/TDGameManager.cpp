#include "TowerDefense/TDGameManager.h"
#include "Engine/EngineBravo.h"
#include "Global/Time.h"
#include "Rendering/Sprite.h"
#include "ResourceManager/ResourceManager.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include <iostream>

TDGameManager::TDGameManager()
    : mMoney(500), mBaseHealth(100), mCurrentWave(0), mMaxWaves(10),
      mSpawnTimer(0.0f), mSpawnInterval(1.0f), 
      mEnemiesToSpawn(0), mEnemiesSpawned(0),
      mGameState(GameState::PLAYING) {}

void TDGameManager::onStart() {
    mGameObject->setTag("GameManager");
    mPath = createPath();
    startWave();
}

void TDGameManager::onUpdate() {
    if (mGameState != GameState::PLAYING) {
        return;
    }
    
    // Check base health
    if (mBaseHealth <= 0) {
        mGameState = GameState::DEFEAT;
        std::cout << "GAME OVER - Base Destroyed!" << std::endl;
        return;
    }
    
    // Spawn enemies for current wave
    if (mEnemiesSpawned < mEnemiesToSpawn) {
        mSpawnTimer += Time::deltaTime;
        if (mSpawnTimer >= mSpawnInterval) {
            spawnEnemy();
            mSpawnTimer = 0.0f;
        }
    }
    
    // Check if wave is complete
    if (mEnemiesSpawned >= mEnemiesToSpawn) {
        checkWaveComplete();
    }
    
    // Check for enemies that reached the end
    Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
    std::vector<std::reference_wrapper<GameObject>> enemies = scene.getGameObjectsWithTag("Enemy");
    
    for (auto& enemyRef : enemies) {
        GameObject& enemy = enemyRef.get();
        auto enemyComponents = enemy.getComponents<TDEnemy>();
        if (!enemyComponents.empty()) {
            TDEnemy& tdEnemy = enemyComponents[0];
            if (tdEnemy.hasReachedEnd()) {
                damageBase(10);
                enemy.setActive(false);
            }
            if (tdEnemy.isDead()) {
                addMoney(tdEnemy.getReward());
            }
        }
    }
    
    updateUI();
}

bool TDGameManager::spendMoney(int amount) {
    if (mMoney >= amount) {
        mMoney -= amount;
        return true;
    }
    return false;
}

void TDGameManager::damageBase(int damage) {
    mBaseHealth -= damage;
    std::cout << "Base damaged! Health: " << mBaseHealth << std::endl;
}

void TDGameManager::startWave() {
    mCurrentWave++;
    
    if (mCurrentWave > mMaxWaves) {
        mGameState = GameState::VICTORY;
        std::cout << "VICTORY - All waves completed!" << std::endl;
        return;
    }
    
    mEnemiesToSpawn = 5 + (mCurrentWave * 3);
    mEnemiesSpawned = 0;
    mSpawnTimer = 0.0f;
    mSpawnInterval = std::max(0.3f, 1.5f - (mCurrentWave * 0.1f));
    
    std::cout << "Wave " << mCurrentWave << " starting with " << mEnemiesToSpawn << " enemies!" << std::endl;
}

void TDGameManager::spawnEnemy() {
    Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
    
    GameObject* enemy = new GameObject();
    
    // Enemy stats increase with wave
    float health = 50.0f + (mCurrentWave * 20.0f);
    float speed = 50.0f + (mCurrentWave * 5.0f);
    int reward = 10 + (mCurrentWave * 2);
    
    enemy->addComponent<TDEnemy>(health, speed, reward, mPath);
    
    // Set starting position
    Transform transform;
    if (!mPath.empty()) {
        transform.position.x = mPath[0].x;
        transform.position.y = mPath[0].y;
    }
    enemy->setTransform(transform);
    
    scene.addGameObject(enemy);
    mEnemiesSpawned++;
}

void TDGameManager::checkWaveComplete() {
    Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
    std::vector<std::reference_wrapper<GameObject>> enemies = scene.getGameObjectsWithTag("Enemy");
    
    if (enemies.empty()) {
        mGameState = GameState::WAVE_COMPLETE;
        std::cout << "Wave " << mCurrentWave << " complete!" << std::endl;
        
        // Give bonus money for completing wave
        addMoney(50 + (mCurrentWave * 10));
        
        // Start next wave after delay
        mSpawnTimer = -3.0f; // 3 second delay
        mGameState = GameState::PLAYING;
        startWave();
    }
}

void TDGameManager::updateUI() {
    // This would update UI elements - for now just print occasionally
    static float uiTimer = 0.0f;
    uiTimer += Time::deltaTime;
    
    if (uiTimer > 2.0f) {
        std::cout << "Wave: " << mCurrentWave << " | Money: $" << mMoney 
                  << " | Base HP: " << mBaseHealth << std::endl;
        uiTimer = 0.0f;
    }
}

std::vector<Waypoint> TDGameManager::createPath() {
    std::vector<Waypoint> path;
    
    // Create a winding path across the screen
    path.push_back({50.0f, 150.0f});
    path.push_back({150.0f, 150.0f});
    path.push_back({150.0f, 100.0f});
    path.push_back({250.0f, 100.0f});
    path.push_back({250.0f, 200.0f});
    path.push_back({350.0f, 200.0f});
    path.push_back({350.0f, 100.0f});
    path.push_back({450.0f, 100.0f});
    
    // Add visual markers for the path
    EngineBravo& engine = EngineBravo::getInstance();
    Scene& scene = engine.getSceneManager().getCurrentScene();
    
    SpriteDef pathMarker = {"Coins/coin_silver.png", Rect(0, 0, 16, 16), 16, 16};
    
    for (const auto& waypoint : path) {
        GameObject* marker = new GameObject();
        marker->setTag("PathMarker");
        
        Transform transform;
        transform.position.x = waypoint.x;
        transform.position.y = waypoint.y;
        marker->setTransform(transform);
        
        Sprite* sprite = engine.getResourceManager().createSprite(pathMarker);
        sprite->setLayer(0);
        marker->addComponent(sprite);
        
        scene.addGameObject(marker);
    }
    
    return path;
}
