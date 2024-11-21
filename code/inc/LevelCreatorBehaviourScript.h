#ifndef LEVELCREATORBEHAVIOURSCRIPT_H
#define LEVELCREATORBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>
#include <Scene.h>
#include <TileMapParser.h>
#include <FSConverter.h>

class LevelCreatorBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;
    std::unique_ptr<Component> clone() const override { return std::make_unique<LevelCreatorBehaviourScript>(*this); }
    friend class LevelManagerBehaviourScript;
    
private:
    void createLevel1();
    void createLevel2();
    void createLevel3();
    void createPlayer(Scene* scene, const TileMapData& tileMapData);
    void createEnemy();
    void createBoss();
    void createLevel(Scene* scene, const TileMapData& tileMapData);
private:
    FSConverter mFsConverter;
};

#endif