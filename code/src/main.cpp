#include <iostream>

#include "Components/IBehaviourScript.h"
#include "Components/ParticleEmitter.h"
#include "Components/RigidBody.h"
#include "Input/Input.h"
#include <Engine/EngineBravo.h>
#include <Engine/SceneManager.h>
#include <GameObject.h>
#include <Scene.h>

#include "SpriteDef.h"

SpriteDef spriteDef = {"DinoSprites.png", Rect(4, 3, 15, 17), 15, 17};

class PlayerBehaviourScript : public IBehaviourScript
{
public:
    void onStart() override
    {
        mGameObject->setTag("Player");

        Sprite* playerSprite = EngineBravo::getInstance().getResourceManager().createSprite(spriteDef);

        mGameObject->addComponent(playerSprite);
    }

    void onUpdate() override {}

    void onCollide(GameObject* aGameObject) override {}

    std::unique_ptr<Component> clone() const override { return std::make_unique<IBehaviourScript>(*this); };
};

void init()
{
    EngineBravo::getInstance().initialize();
    EngineBravo::getInstance().getRenderSystem().setBackgroundColor(Color(0xe6, 0x19, 0xd3));
    SceneManager& sceneManager = EngineBravo::getInstance().getSceneManager();

    Scene& scene = sceneManager.createScene("only_scene");

    Camera* camera = new Camera;
    camera->setTag("MainCamera");
    camera->setActive(true);

    camera->setTransform(Transform(Vector2(0, 0)));
    camera->setWidth(16 * 20);
    camera->setHeight(9 * 20);

    camera->setBackgroundColor(Color(0, 0, 0));

    scene.addGameObject(camera);

    GameObject* initObject = new GameObject;
    initObject->addComponent<PlayerBehaviourScript>();
    scene.addGameObject(initObject);

    sceneManager.requestSceneChange("only_scene");

    EngineBravo::getInstance().run();
    return;
}

int main()
{
    init();
    return 0;
}
