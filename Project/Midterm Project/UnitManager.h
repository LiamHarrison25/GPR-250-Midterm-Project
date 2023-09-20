#pragma once

#include <Trackable.h>
#include <vector>
#include <MemoryPool.h>


class Unit;
class Vector2D;
class Animation;

class UnitManager :public Trackable
{
public:

	UnitManager();
	UnitManager(Uint32 maxSize);
	~UnitManager();

	void addUnit(Animation* animation, Vector2D location, Vector2D velocity, float accel, float speed);
	void deleteUnit(int unitNumber);
	int getListSize();
	Unit* getUnit(int unitNumber);
	void clear();
	void update(float dt);
	void draw();
	void freezeAllUnits();

private:

	const int MAX_SIZE_PRECAUTION = 10;
	
	bool mAllUnitsPaused;
	std::vector<Unit*> mUnitList;
	MemoryPool mPool;

};
