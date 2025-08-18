#include <iostream>

#include "BehaviourScripts/IBehaviourScript.h"
#include "Engine/EngineBravo.h"
#include "GameObject/GameObject.h"
#include "Input/Input.h"
#include "Particles/ParticleEmitter.h"
#include "Physics/RigidBody.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

#include "Structs/SpriteDef.h"

SpriteDef spriteDef = {"DinoSprites.png", Rect(4, 3, 15, 17), 15, 17};

class PlayerBehaviourScript : public IBehaviourScript
{
public:
    void onStart() override
    {
        mGameObject->setTag("Player");

        Sprite* playerSprite = EngineBravo::getInstance().getResourceManager().createSprite(spriteDef);

        mGameObject->addComponent(playerSprite);

        AudioSource* source = new AudioSource("Audio/gun1.wav");

        mGameObject->addComponent(source);
    }

    void onUpdate() override
    {
        Input& input = Input::getInstance();

        float movementSpeed = 1.5;

        if (input.getKey(Key::Key_W))
        {
            mGameObject->getTransformRef().position.y -= movementSpeed;
        }
        if (input.getKey(Key::Key_A))
        {
            mGameObject->getTransformRef().position.x -= movementSpeed;
        }
        if (input.getKey(Key::Key_S))
        {
            mGameObject->getTransformRef().position.y += movementSpeed;
        }
        if (input.getKey(Key::Key_D))
        {
            mGameObject->getTransformRef().position.x += movementSpeed;
        }

        if (input.getKeyDown(Key::Key_Space))
        {
            mGameObject->getComponents<AudioSource>()[0].get().play();
        }
    }

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
