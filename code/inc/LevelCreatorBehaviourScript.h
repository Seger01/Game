#ifndef LEVELCREATORBEHAVIOURSCRIPT_H
#define LEVELCREATORBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <FSConverter.h>
#include <GameObject.h>
#include <Scene.h>
#include <TileMapParser.h>

class LevelCreatorBehaviourScript : public IBehaviourScript {
public:
    void onStart() override;
    void onUpdate() override;

    //void createLevel(Scene* scene, const TileMapData& tileMapData);
    void setPlayerStartPosition(Scene* scene, const TileMapData& tileMapData);
    std::unique_ptr<Component> clone() const override { return std::make_unique<LevelCreatorBehaviourScript>(*this); }
    friend class LevelManagerBehaviourScript;

private:
    void createLevel1();
    void createLevel2();
    void createLevel3();
    void createDemoNetworkingLevel();
    void createPlayer(Scene* scene, const TileMapData& tileMapData);
    void addRoomEntries(Scene* scene, const TileMapData& tileMapData);
    void addLevelEndTriggers(Scene* scene, const TileMapData& tileMapData);

private:
    FSConverter mFsConverter;
    bool mPlayerPositionSet = false;
    TileMapData mTileMapData;
};

#endif
