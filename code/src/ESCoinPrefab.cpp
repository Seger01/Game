#include "ECCoinPrefab.h"

ECCoinPrefab::ECCoinPrefab() {
    mCoinWidth = 16;
    mCoinHeight = 16;
    mCoinSpritePosition = {0, 0}; // Adjust the sprite position as needed

    FSConverter fsConverter;
    std::string coinSpritePath = fsConverter.getResourcePath("Coins/ec_coin_circle.png");
    mCoinSpriteDef = {
        coinSpritePath,
        Rect{mCoinSpritePosition.x, mCoinSpritePosition.y, mCoinWidth, mCoinHeight},
        mCoinWidth, mCoinHeight
    };
}

GameObject* ECCoinPrefab::createECCoinPrefab() {
    GameObject* coinPrefab = new GameObject;
    coinPrefab->setTag("ECCoin");
    addSprite(coinPrefab);
    return coinPrefab;
}

void ECCoinPrefab::addSprite(GameObject* gameObject) {
    Sprite* coinSprite = EngineBravo::getInstance().getResourceManager().createSprite(mCoinSpriteDef);
    coinSprite->setLayer(3);
    gameObject->addComponent(coinSprite);
}