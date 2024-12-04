#pragma once
#include "GameObject.h"

class EnemyPrefab {
public: 
    EnemyPrefab();
    GameObject* createEnemyPrefab();

private:
    void setTransform(GameObject *gameObject);
    void addSprite(GameObject *gameObject);
    void addRigidBody(GameObject *gameObject);
    void addCollider(GameObject *gameObject);
    static void addAnimations(GameObject* gameObject);
private: 

};