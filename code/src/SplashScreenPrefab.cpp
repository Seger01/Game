#include "SplashScreenPrefab.h"

#include <EngineBravo.h>

GameObject *SplashScreenPrefab::create()
{
    GameObject *splashScreen = new GameObject;
    splashScreen->setName("SplashScreen");
    SpriteDef logo = {"Engine_logo/Engine-BRAVO_logo.png", Rect(), 200, 200};
    Sprite *sprite = EngineBravo::getInstance().getResourceManager().createSprite(logo);
    splashScreen->addComponent(sprite);

    return splashScreen;
}