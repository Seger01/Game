#pragma once

#include "BehaviourScripts/IBehaviourScript.h"
#include "GameObject/GameObject.h"
#include "TowerDefense/TDEnemy.h"
#include <vector>

enum class GameState {
    PLAYING,
    WAVE_COMPLETE,
    VICTORY,
    DEFEAT
};

class TDGameManager : public IBehaviourScript {
public:
    TDGameManager();
    
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override {}
    
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<TDGameManager>(*this); 
    }
    
    void addMoney(int amount) { mMoney += amount; }
    bool spendMoney(int amount);
    int getMoney() const { return mMoney; }
    
    void damageBase(int damage);
    int getBaseHealth() const { return mBaseHealth; }
    
    int getCurrentWave() const { return mCurrentWave; }
    GameState getGameState() const { return mGameState; }
    
private:
    void startWave();
    void spawnEnemy();
    void checkWaveComplete();
    void updateUI();
    std::vector<Waypoint> createPath();
    
    int mMoney;
    int mBaseHealth;
    int mCurrentWave;
    int mMaxWaves;
    
    float mSpawnTimer;
    float mSpawnInterval;
    int mEnemiesToSpawn;
    int mEnemiesSpawned;
    
    GameState mGameState;
    std::vector<Waypoint> mPath;
};
