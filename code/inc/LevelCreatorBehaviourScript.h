#ifndef LEVELCREATORBEHAVIOURSCRIPT_H
#define LEVELCREATORBEHAVIOURSCRIPT_H

#include <Components/IBehaviourScript.h>
#include <GameObject.h>
#include <Global/FSConverter.h>
#include <Scene.h>
#include <TileMapParser.h>

class LevelCreatorBehaviourScript : public IBehaviourScript
{
public:
	void onStart() override;
	void onUpdate() override;

	// void createLevel(Scene* scene, const TileMapData& tileMapData);
	void setPlayerStartPosition(Scene* scene, const TileMapData& tileMapData);

	std::unique_ptr<Component> clone() const override { return std::make_unique<LevelCreatorBehaviourScript>(*this); }

	void createObjects(Scene* scene, const TileMapData& tileMapData);

	friend class LevelManagerBehaviourScript;

private:
	void createLevel1();
	void createLevel2();
	void createLevel3();
	void createDemoNetworkingLevel();
	void createPlayer(Scene* scene, const TileMapData& tileMapData);
	void addRoomEntries(Scene* scene, const TileMapData& tileMapData);
	void addLevelEndTriggers(Scene* scene, const TileMapData& tileMapData);
	void createRoomEntry(Scene* scene, const MapObject& mapObject, const TileMapData& tileMapData) const;
	void createLevelEndTrigger(Scene* scene, const MapObject& mapObject) const;
	void addTriggerCollider(GameObject* gameObject, const MapObject& mapObject) const;
	void setDoorsLayer(Scene* scene) const;

private:
	FSConverter mFsConverter;
	bool mPlayerPositionSet = false;
	TileMapData mTileMapData;
};

#endif
