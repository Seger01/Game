#include "BSCoinPrefab.h"

BSCoinPrefab::BSCoinPrefab() {
    mCoinWidth = 16;
    mCoinHeight = 16;
    mCoinSpritePosition = {0, 0}; // Adjust the sprite position as needed

    FSConverter fsConverter;
    std::string coinSpritePath = fsConverter.getResourcePath("Coins/bs_coin_circle.png");
    mCoinSpriteDef = {
        coinSpritePath,
        Rect{mCoinSpritePosition.x, mCoinSpritePosition.y, mCoinWidth, mCoinHeight},
        mCoinWidth, mCoinHeight
    };
}

GameObject* BSCoinPrefab::createBSCoinPrefab() {
    GameObject* coinPrefab = new GameObject;
    coinPrefab->setTag("BSCoin");
    addSprite(coinPrefab);
    return coinPrefab;
}

void BSCoinPrefab::addSprite(GameObject* gameObject) {
    Sprite* coinSprite = EngineBravo::getInstance().getResourceManager().createSprite(mCoinSpriteDef);
    coinSprite->setLayer(3);
    gameObject->addComponent(coinSprite);
}