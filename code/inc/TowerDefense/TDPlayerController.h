#pragma once

#include "Components/IBehaviourScript.h"
#include "GameObject/GameObject.h"
#include "TowerDefense/TDTower.h"
#include "TowerDefense/TDGameManager.h"

class TDPlayerController : public IBehaviourScript {
public:
    TDPlayerController();
    
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override {}
    
    std::unique_ptr<Component> clone() const override { 
        return std::make_unique<TDPlayerController>(*this); 
    }
    
private:
    void handleInput();
    void placeTower(TowerType type, float x, float y);
    TDGameManager* getGameManager();
    
    TowerType mSelectedTowerType;
    TDGameManager* mGameManager;
};
