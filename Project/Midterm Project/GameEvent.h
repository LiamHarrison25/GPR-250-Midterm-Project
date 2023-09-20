#pragma once


#include <Trackable.h>
#include <Event.h>

enum GameEventType
{
	QUIT_GAME,
	DELETE_UNIT,
	ADD_UNIT,
	FREEZE,
	CHANGE_SPRITE, 
	SLOW_DOWN, 
	SPEED_UP 
};

class GameEvent :public Event
{
public:
	GameEvent(GameEventType type);
	virtual ~GameEvent();

private:

};
