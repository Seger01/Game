#pragma once
#include <GameObject.h>

class Button;
class Scene;
class MainMenuPrefabFactory {
public:
    static GameObject* createMainMenuPrefab();
    static Button* createDefaultButton(GameObject* gameObject, Scene* aScene, const std::string& text,
                                       const std::string& tag, const std::string& buttonText, int menuStartX,
                                       int menuStartY);

private:
    static void setTag(GameObject* gameObject);
    static void setBackground(GameObject* gameObject);
    static void addBehaviour(GameObject* gameObject);
};
