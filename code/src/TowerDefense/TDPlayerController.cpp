#include "TowerDefense/TDPlayerController.h"
#include "Engine/EngineBravo.h"
#include "Input/Input.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include <iostream>

TDPlayerController::TDPlayerController()
    : mSelectedTowerType(TowerType::BASIC), mGameManager(nullptr) {}

void TDPlayerController::onStart() {
    mGameObject->setTag("PlayerController");
    std::cout << "=== Tower Defense Controls ===" << std::endl;
    std::cout << "1: Select Basic Tower ($100)" << std::endl;
    std::cout << "2: Select Rapid Tower ($150)" << std::endl;
    std::cout << "3: Select Sniper Tower ($250)" << std::endl;
    std::cout << "4: Select Splash Tower ($200)" << std::endl;
    std::cout << "Click to place tower" << std::endl;
}

void TDPlayerController::onUpdate() {
    handleInput();
}

void TDPlayerController::handleInput() {
    Input& input = Input::getInstance();
    
    // Select tower types
    if (input.getKeyDown(Key::Key_1)) {
        mSelectedTowerType = TowerType::BASIC;
        std::cout << "Selected: Basic Tower ($100)" << std::endl;
    }
    else if (input.getKeyDown(Key::Key_2)) {
        mSelectedTowerType = TowerType::RAPID;
        std::cout << "Selected: Rapid Tower ($150)" << std::endl;
    }
    else if (input.getKeyDown(Key::Key_3)) {
        mSelectedTowerType = TowerType::SNIPER;
        std::cout << "Selected: Sniper Tower ($250)" << std::endl;
    }
    else if (input.getKeyDown(Key::Key_4)) {
        mSelectedTowerType = TowerType::SPLASH;
        std::cout << "Selected: Splash Tower ($200)" << std::endl;
    }
    
    // Place tower with mouse click
    if (input.getMouseButtonDown(0)) {
        Point mousePos = input.getMousePosition();
        
        // Convert mouse position to world coordinates
        // For now, using simple mouse position
        placeTower(mSelectedTowerType, mousePos.x, mousePos.y);
    }
}

void TDPlayerController::placeTower(TowerType type, float x, float y) {
    TDGameManager* gm = getGameManager();
    if (!gm) {
        return;
    }
    
    // Create tower with the selected type
    TDTower tempTower(type);
    int cost = tempTower.getCost();
    
    if (gm->spendMoney(cost)) {
        GameObject* tower = new GameObject();
        tower->addComponent<TDTower>(type);
        
        Transform transform;
        transform.position.x = x;
        transform.position.y = y;
        tower->setTransform(transform);
        
        Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
        scene.addGameObject(tower);
        
        std::cout << "Tower placed at (" << x << ", " << y << ") - Money: $" << gm->getMoney() << std::endl;
    } else {
        std::cout << "Not enough money! Need $" << cost << ", have $" << gm->getMoney() << std::endl;
    }
}

TDGameManager* TDPlayerController::getGameManager() {
    if (!mGameManager) {
        Scene& scene = EngineBravo::getInstance().getSceneManager().getCurrentScene();
        auto managers = scene.getGameObjectsWithTag("GameManager");
        
        if (!managers.empty()) {
            GameObject& managerObj = managers[0].get();
            auto components = managerObj.getComponents<TDGameManager>();
            if (!components.empty()) {
                mGameManager = &components[0].get();
            }
        }
    }
    
    return mGameManager;
}
