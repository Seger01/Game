#ifndef DEMOBULLETSPAWNER_H
#define DEMOBULLETSPAWNER_H

#include <IBehaviourScript.h>
#include "BulletPrefab.h"
#include <vector>

class DemoBulletSpawner : public IBehaviourScript {
public:
    DemoBulletSpawner();
    void onStart() override;
    void onUpdate() override;
    void onCollide(GameObject* aGameObject) override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<DemoBulletSpawner>(*this); }

private:
    BulletPrefabFactory mBulletFactory;
    std::vector<GameObject*> mBullets;
    int mMaxBullets;
    float mSpawnInterval;
    float mTimeSinceLastSpawn;
    GameObject* mTextObject;
};

#endif // DEMOBULLETSPAWNER_H