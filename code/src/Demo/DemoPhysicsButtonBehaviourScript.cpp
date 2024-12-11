#include "DemoPhysicsButtonBehaviourScript.h"
#include <BoxCollider.h>
#include <CircleCollider.h>
#include <EngineBravo.h>
#include <FSConverter.h>
#include <PhysicsManager.h>
#include <RigidBody.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Sprite.h>
#include <SpriteDef.h>
#include <iostream>

DemoPhysicsButtonBehaviourScript::DemoPhysicsButtonBehaviourScript() {}

void DemoPhysicsButtonBehaviourScript::onStart()
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();
    PhysicsManager& physicsManager = engine.getPhysicsManager();

    mButtonPressedBox = false;
    mButtonPressedCircle = false;
    mButtonPressedGravity = false;
    mButtonPressedFilter = false;
    mBoxGravitySpawned = false;
    mBoxSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{304, 402, 16, 14}, 16, 14};
    mCircleSpriteDef = {"Dungeontileset/0x72_DungeonTilesetII_v1.7.png", Rect{292, 439, 7, 6}, 7, 6};
    physicsManager.getPhysicsEngine().getWorld().setGravity(Vector2(0.0f, 9.8f));
}

void DemoPhysicsButtonBehaviourScript::onUpdate() {}

void DemoPhysicsButtonBehaviourScript::onCollide(GameObject* aGameObject)
{
    if (aGameObject == nullptr)
    {
        return;
    }
    if (aGameObject->getTag() == "Player")
    {
        updateButtonState(mGameObject->getTag());
    }
}

void DemoPhysicsButtonBehaviourScript::updateButtonState(const std::string& buttonTag)
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    if (buttonTag == "ButtonBox")
    {
        if (!mButtonPressedBox)
        {
            spawnBox(Vector2(176, 488), "Box", Vector2(-2000, -10000));
            mButtonPressedBox = true;
        }
        else
        {
            removeBox("Box");
            mButtonPressedBox = false;
        }
        updateButtonSprites(mButtonPressedBox);
    }
    else if (buttonTag == "ButtonCircle")
    {
        if (!mButtonPressedCircle)
        {
            spawnCircle(Vector2(176, 512), "Circle1");
            mButtonPressedCircle = true;
        }
        else
        {
            removeCircle("Circle1");
            mButtonPressedCircle = false;
        }
        updateButtonSprites(mButtonPressedCircle);
    }
    else if (buttonTag == "ButtonGravity")
    {
        toggleGravity();
        updateButtonSprites(mButtonPressedGravity);
    }
    else if (buttonTag == "ButtonFilter")
    {
        std::cout << "ButtonFilter" << std::endl;
        if (!mButtonPressedFilter)
        {
            spawnBox(Vector2(96, 624), "ButtonFilterBox", Vector2(-2000, -10000));
            spawnBox(Vector2(112, 624), "ButtonFilterBox", Vector2(2000, -10000));
            spawnCircle(Vector2(128, 624), "ButtonFilterCircle");
            spawnCircle(Vector2(144, 624), "ButtonFilterCircle");

            std::vector<GameObject*> boxes =
                EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("Box");
            for (GameObject* box : boxes)
            {
                if (box->hasComponent<BoxCollider>())
                {
                    box->getComponents<BoxCollider>()[0]->setCollideCategory(1);
                    box->getComponents<BoxCollider>()[0]->setCollideWithCategory({1});
                }
            }

            std::vector<GameObject*> circles =
                EngineBravo::getInstance().getSceneManager().getCurrentScene()->getGameObjectsWithTag("Circle");
            for (GameObject* circle : circles)
            {
                if (circle->hasComponent<CircleCollider>())
                {
                    circle->getComponents<CircleCollider>()[0]->setCollideCategory(2);
                    circle->getComponents<CircleCollider>()[0]->setCollideWithCategory({2});
                }
            }

            mButtonPressedFilter = true;
        }
        else
        {
            removeBox("ButtonFilterBox");
            removeCircle("ButtonFilterCircle");
            mButtonPressedFilter = false;
        }
        updateButtonSprites(mButtonPressedFilter);
    }
}

void DemoPhysicsButtonBehaviourScript::updateButtonSprites(bool isActive)
{
    for (Component* component : mGameObject->getComponents<Sprite>())
    {
        if (component->getTag() == "ButtonDownSprite")
        {
            component->setActive(isActive);
        }
        else if (component->getTag() == "ButtonUpSprite")
        {
            component->setActive(!isActive);
        }
    }
}

void DemoPhysicsButtonBehaviourScript::spawnBox(const Vector2& aPosition, const std::string& aName, const Vector2& aForce)
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    GameObject* box = new GameObject();
    box->setTag("Box");
    box->setName(aName);
    Transform transform;
    transform.position = aPosition;
    box->setTransform(transform);

    Sprite* sprite = engine.getResourceManager().createSprite(mBoxSpriteDef);
    sprite->setLayer(3);
    box->addComponent(sprite);

    RigidBody* rigidBody = new RigidBody();
    rigidBody->setDensity(1.0f);
    rigidBody->setRestitution(1.0f);
    rigidBody->addForce(aForce);
    box->addComponent(rigidBody);

    BoxCollider* boxCollider = new BoxCollider();
    boxCollider->setWidth(sprite->getWidth() + 1);
    boxCollider->setHeight(sprite->getHeight());
    boxCollider->setTrigger(false);
    box->addComponent(boxCollider);

    scene->addGameObject(box);
}

void DemoPhysicsButtonBehaviourScript::spawnCircle(const Vector2& aPosition, const std::string& aName)
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    GameObject* circle = new GameObject();
    circle->setTag("Circle");
    circle->setName(aName);
    Transform transform;
    transform.position = aPosition;
    circle->setTransform(transform);

    Sprite* sprite = engine.getResourceManager().createSprite(mCircleSpriteDef);
    sprite->setLayer(3);
    circle->addComponent(sprite);

    RigidBody* rigidBody = new RigidBody();
    rigidBody->setDensity(1.0f);
    rigidBody->setRestitution(1.0f);
    rigidBody->addForce(Vector2(-200, -1000));
    circle->addComponent(rigidBody);

    CircleCollider* circleCollider = new CircleCollider();
    circleCollider->setRadius(sprite->getWidth() / 2);
    circleCollider->setIsTrigger(false);
    circle->addComponent(circleCollider);

    scene->addGameObject(circle);
}

void DemoPhysicsButtonBehaviourScript::removeBox(const std::string& aName)
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    auto boxes = scene->getGameObjectsWithTag("Box");
    for (auto& box : boxes)
    {
        if (aName.empty() || box->getName() == aName)
        {
            scene->requestGameObjectRemoval(box);
        }
    }
}

void DemoPhysicsButtonBehaviourScript::removeCircle(const std::string& aName)
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    auto circles = scene->getGameObjectsWithTag("Circle");
    for (auto& circle : circles)
    {
        if (aName.empty() || circle->getName() == aName)
        {
            scene->requestGameObjectRemoval(circle);
        }
    }
}

void DemoPhysicsButtonBehaviourScript::toggleGravity()
{
    EngineBravo& engine = EngineBravo::getInstance();
    SceneManager& sceneManager = engine.getSceneManager();
    Scene* scene = sceneManager.getCurrentScene();

    // Remove the existing box if it exists
    removeBox("BoxGravity");

    // Toggle gravity state
    mButtonPressedGravity = !mButtonPressedGravity;

    // Spawn a new box with the appropriate gravity state
    spawnBox(Vector2(160, 336), "BoxGravity", Vector2(0, 0));

    // Set the gravity scale for the new box
    std::vector<GameObject*> boxes = scene->getGameObjectsWithTag("Box");
    for (GameObject* box : boxes)
    {
        if (box->getName() == "BoxGravity" && box->hasComponent<RigidBody>())
        {
            RigidBody* rigidBody = box->getComponents<RigidBody>()[0];
            rigidBody->setHasGravity(mButtonPressedGravity);
            rigidBody->setGravityScale(mButtonPressedGravity ? 1.0f : 0.0f);
			rigidBody->setRestitution(0.8f);
        }
    }
}