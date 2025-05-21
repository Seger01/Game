#pragma once

#include <Components/IBehaviourScript.h>
#include <GameObject.h>
#include <SpriteDef.h>
#include <TileMapParser.h>
#include <iostream>
#include <vector>

class RoomBehaviourScript : public IBehaviourScript
{
public:
	RoomBehaviourScript(const std::string& roomID, const std::vector<MapObject>& enemySpawns)
		: mRoomID(roomID), mEnemySpawns(enemySpawns)
	{
	}

	void onStart() override;
	void onUpdate() override;
	void onCollide(GameObject* aGameObject) override;

	std::unique_ptr<Component> clone() const override { return std::make_unique<RoomBehaviourScript>(*this); }

private:
	void spawnEnemies();
	void updateDoors(const SpriteDef& spriteDef);
	void openDoors();
	void closeDoors();

private:
	std::string mRoomID;
	std::vector<MapObject> mEnemySpawns;
	SpriteDef mClosedDoorSpriteDef;
	SpriteDef mOpenDoorSpriteDef;
	SpriteDef mEnemyFrameDef;
	bool mDoorsOpen = true;
};
