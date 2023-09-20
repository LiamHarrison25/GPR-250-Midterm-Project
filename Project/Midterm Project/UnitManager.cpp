
#include "UnitManager.h"
#include "Unit.h"

UnitManager::UnitManager() 
	:mPool(0, 0)
{
	mAllUnitsPaused = false;
}

UnitManager::UnitManager(Uint32 maxSize)
	:mPool(maxSize, sizeof(Unit) + MAX_SIZE_PRECAUTION)
{
	mAllUnitsPaused = false;
}

UnitManager::~UnitManager() 
{
	clear();
}

void UnitManager::addUnit(Animation* animation, Vector2D location, Vector2D velocity, float accel, float speed)
{
	Unit* unit = nullptr;
	Byte* ptr = mPool.allocateObject();

	if (ptr != nullptr)
	{
		unit = new (ptr)Unit(animation, location, velocity, accel, speed);
		mUnitList.push_back(unit);

	}
	
	if (mAllUnitsPaused)
	{
		int lastUnitAdded = mUnitList.size() - 1;
		mUnitList[lastUnitAdded]->togglePausedGame();
	}
}

void UnitManager::deleteUnit(int unitNumber)
{
	mUnitList[unitNumber]->~Unit();
	mPool.freeObject((Byte*)mUnitList[unitNumber]);
	mUnitList.erase(mUnitList.begin() + unitNumber);
}

int UnitManager::getListSize()
{
	return mUnitList.size();
}

Unit* UnitManager::getUnit(int unitNumber) 
{
	return mUnitList[unitNumber];
}

void UnitManager::clear()
{
	int size = getListSize() - 1;
	int i;
	for (i = 0; i < size; i++)
	{
		mUnitList[i]->~Unit();
		mPool.freeObject((Byte*)mUnitList[i]);
	}
	mUnitList.clear();
}

void UnitManager::update(float dt) 
{
	//updates every unit

	unsigned int i;
	for (i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->update(dt);
	}
	
}

void UnitManager::draw()
{
	unsigned int i;
	for (i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->draw();
	}
}

void UnitManager::freezeAllUnits()
{
	mAllUnitsPaused = !mAllUnitsPaused;
	unsigned int i;
	for (i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->togglePausedGame();
	}
}
