#include <iostream>

#include "Engine/EngineBravo.h"
#include "GameObject/GameObject.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include "TowerDefense/TDGameManager.h"
#include "TowerDefense/TDPlayerController.h"
#include "Structs/SpriteDef.h"

void init()
{
    EngineBravo::getInstance().initialize();
    
    // Set a nice green background for tower defense
    EngineBravo::getInstance().getRenderSystem().setBackgroundColor(Color(50, 150, 50));
    
    SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();
    Scene& scene = sceneManager.createScene("tower_defense");

    // Create camera
    Camera* camera = new Camera;
    camera->setTag("MainCamera");
    camera->setActive(true);
    camera->setTransform(Transform(Vector2(250, 150)));
    camera->setWidth(500);
    camera->setHeight(300);
    camera->setBackgroundColor(Color(50, 150, 50));
    scene.addGameObject(camera);

    // Create game manager
    GameObject* gameManager = new GameObject;
    gameManager->addComponent<TDGameManager>();
    scene.addGameObject(gameManager);

    // Create player controller
    GameObject* playerController = new GameObject;
    playerController->addComponent<TDPlayerController>();
    scene.addGameObject(playerController);

    std::cout << "\n=== TOWER DEFENSE GAME ===" << std::endl;
    std::cout << "Defend your base from waves of enemies!" << std::endl;
    std::cout << "Place towers to destroy enemies before they reach the end." << std::endl;
    std::cout << "\nControls:" << std::endl;
    std::cout << "  1-4: Select tower type" << std::endl;
    std::cout << "  Mouse Click: Place selected tower" << std::endl;
    std::cout << "\nStarting money: $300" << std::endl;
    std::cout << "Base health: 100" << std::endl;
    std::cout << "==============================\n" << std::endl;

    sceneManager.requestSceneChange("tower_defense");
    EngineBravo::getInstance().run();
}

int main()
{
    init();
    return 0;
}
